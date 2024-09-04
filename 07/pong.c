#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <signal.h>
#include <unistd.h>

#define QUEUE_NAME "/pingpong_queue"
#define MSG_SIZE 256

struct msg_buffer {
    char msg_text[MSG_SIZE];
};

mqd_t mq;

void cleanup(int signum) {
    mq_unlink(QUEUE_NAME);  
    exit(0);
}

int main() {
    signal(SIGINT, cleanup);  

    struct msg_buffer message;

    mq = mq_open(QUEUE_NAME, O_RDWR);
    if (mq == (mqd_t) -1) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    while (1) {
        mq_receive(mq, message.msg_text, sizeof(message.msg_text), NULL);  
        printf("Получено от Ping: %s\n", message.msg_text);
        
        if (strcmp(message.msg_text, "Exit") == 0) {
            strcpy(message.msg_text, "Exit");
            mq_send(mq, message.msg_text, sizeof(message.msg_text), 0);
            printf("Завершение общения.\n");
            break;
        }

        strcpy(message.msg_text, "Pong");
        mq_send(mq, message.msg_text, sizeof(message.msg_text), 0);
        printf("Pong отправлено: %s\n", message.msg_text);
    }

    cleanup(0);  
    return 0;
}