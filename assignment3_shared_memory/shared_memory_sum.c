#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/wait.h>

#define NUM_PROCESSES 100

void sem_op(int semid, int op) {
    struct sembuf sb;
    sb.sem_num = 0;
    sb.sem_op = op;
    sb.sem_flg = 0;
    semop(semid, &sb, 1);
}

int main() {
    int i;

    int shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    int *shared_sum = (int *)shmat(shmid, NULL, 0);
    if (shared_sum == (int *)-1) {
        perror("shmat");
        exit(1);
    }

    *shared_sum = 0;

    int semid = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666);
    if (semid < 0) {
        perror("semget");
        exit(1);
    }

    if (semctl(semid, 0, SETVAL, 1) == -1) {
        perror("semctl");
        exit(1);
    }

    for (i = 1; i <= NUM_PROCESSES; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(1);
        }
        if (pid == 0) {
            sem_op(semid, -1);

            int before = *shared_sum;
            *shared_sum += i;
            int after = *shared_sum;

            printf("Process %d: Added %d, sum changed from %d to %d\n", getpid(), i, before, after);

            sem_op(semid, 1);
            exit(0);
        }
    }

    for (i = 0; i < NUM_PROCESSES; i++) {
        wait(NULL);
    }

    printf("Final Sum from 1 to 100 is: %d\n", *shared_sum);

    shmdt(shared_sum);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID);

    return 0;
}

