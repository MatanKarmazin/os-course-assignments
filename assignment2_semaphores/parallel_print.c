#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define N 5 
#define MAX 100

void sem_op(int semid, int semnum, int val) {
    struct sembuf op;
    op.sem_num = semnum;
    op.sem_op = val;
    op.sem_flg = 0;
    semop(semid, &op, 1);
}

void sem_wait(int semid, int semnum) {
    sem_op(semid, semnum, -4);
}

void sem_signal_all_others(int semid, int self_id) {
    for (int i = 0; i < N; i++) {
        if (i != self_id) {
            sem_op(semid, i, 1);
        }
    }
}

int main() {
    key_t key = ftok("parallel_print.c", 65); 
    int semid = semget(key, N, 0666 | IPC_CREAT); 

    for (int i = 0; i < N; i++) {
        semctl(semid, i, SETVAL, N - 1 - i);  
    }
    for (int i = 0; i < N; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            int index = i; 
            for (int num = index + 1; num <= MAX; num += N) {
                sem_wait(semid, index);       
                printf("Process %d: %d\n", index + 1, num);
                fflush(stdout);             
                sem_signal_all_others(semid, index); 
            }
            exit(0);  
        }
    }
    for (int i = 0; i < N; i++) {
        wait(NULL);
    }

    semctl(semid, 0, IPC_RMID);
    return 0;
}