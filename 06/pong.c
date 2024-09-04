#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <signal.h>

#define MSG_SIZE 256
#define QUEUE_KEY 12345

struct msg_buffer {
    long msg_type;
    char msg_text[MSG_SIZE];
};

int msgid;

void cleanup(int signum) {
    msgctl(msgid, IPC_RMID, NULL);  
    exit(0);
}

int main() {
    signal(SIGINT, cleanup);  

    struct msg_buffer message;

    msgid = msgget(QUEUE_KEY, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    while (1) {
        msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0); 
        printf("Получено от Ping: %s\n", message.msg_text);
        
        if (strcmp(message.msg_text, "Exit") == 0) {
            message.msg_type = 2;  
            strcpy(message.msg_text, "Exit");
            msgsnd(msgid, &message, sizeof(message.msg_text), 0);
            printf("Завершение общения.\n");
            break;
        }

        message.msg_type = 2;  
        strcpy(message.msg_text, "Pong");
        msgsnd(msgid, &message, sizeof(message.msg_text), 0);
        printf("Pong отправлено: %s\n", message.msg_text);
    }

    cleanup(0);  
    return 0;
}