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

    message.msg_type = 1;  
    strcpy(message.msg_text, "Ping");
    
    while (1) {
        msgsnd(msgid, &message, sizeof(message.msg_text), 0);
        printf("Ping отправлено: %s\n", message.msg_text);
        
        msgrcv(msgid, &message, sizeof(message.msg_text), 2, 0);  
        printf("Получено от Pong: %s\n", message.msg_text);
        
        if (strcmp(message.msg_text, "Exit") == 0) {
            printf("Завершение общения.\n");
            break;
        }
    }

    cleanup(0);  
    return 0;
}