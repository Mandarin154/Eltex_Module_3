#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    char command[1024];
    char *args[1024];

    while (1) {
        printf("> ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0; 

        int argc = 0;
        char *token = strtok(command, " ");
        while (token != NULL) {
            args[argc++] = token;
            token = strtok(NULL, " ");
        }
        args[argc] = NULL; 

        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        pid_t pid = fork();
        if (pid == -1) {
            perror("Ошибка при создании процесса");
            continue;
        }

        if (pid == 0) { 
            if (strcmp(args[0], "sum") == 0) {
                execv("./sum", args);
            } else if (strcmp(args[0], "concat") == 0) {
                execv("./concat", args);
            } else if (strcmp(args[0], "max") == 0) {
                execv("./max", args);
            } else if (strcmp(args[0], "longest") == 0) {
                execv("./longest", args);
            } else {
                printf("Неизвестная команда.\n");
                exit(1);
            }
            perror("Ошибка execv"); 
            exit(1);
        } else { 
            wait(NULL); 
        }
    }

    return 0;
}