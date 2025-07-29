#define MAX 100
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

char *isValidCommand(char *cmd);
int isFileExists(char *filePath);

int main(int argc, const char *argv[]) {
    char input[MAX];
    char *command;
    char *args[10];
    int status;
    pid_t pid;

    while (1) {
        printf("$ ");
        fgets(input, MAX, stdin);
        input[strlen(input) - 1] = '\0';
        if (strcmp(input, "leave") == 0) {
            exit(0);
        }
        int i = 0;
        char *token = strtok(input, " ");
        while (token != NULL && i < 9) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;
        command = args[0];
        char *filePath = isValidCommand(command);
        if (filePath == NULL) {
            printf("%s - INVALID COMMAND\n", command);
        } else {
            pid = fork();
            if (pid == 0) { // Child process
                execv(filePath, args);
                perror("execv failed");
                exit(1);
            } else if (pid > 0) { // Parent process
                waitpid(pid, &status, 0);
            } else {
                perror("fork failed");
            }
            free(filePath); // Free allocated memory
        }
    }
    return 0;
}

char *isValidCommand(char *cmd) {
    char *pathVar = getenv("PATH");
    if (!pathVar) return NULL;

    char *pathCopy = strdup(pathVar);
    char *tempDir = strtok(pathCopy, ":");
    char filePath[MAX];

    while (tempDir != NULL) {
        snprintf(filePath, MAX, "%s/%s", tempDir, cmd);
        if (isFileExists(filePath)) {
            free(pathCopy);
            return strdup(filePath);
        }
        tempDir = strtok(NULL, ":");
    }
    free(pathCopy);
    return NULL;
}

int isFileExists(char *filePath) {
    return access(filePath, X_OK) == 0;
}