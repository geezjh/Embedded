#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

typedef struct
{
    long type;
    char mtext[32];
} msg_t;

pthread_mutex_t tid_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_t send_tid = 0;
pthread_t recv_tid = 0;

void *sender_thread(void *arg)
{
    int msgid = *((int *)arg);
    pthread_mutex_lock(&tid_mutex);
    send_tid = pthread_self();
    pthread_mutex_unlock(&tid_mutex);

    while (1)
    {
        msg_t msg;
        msg.type = 2; 
        fgets(msg.mtext, sizeof(msg.mtext), stdin);
        strtok(msg.mtext, "\n"); // 去除换行符

        msgsnd(msgid, &msg, sizeof(msg.mtext), 0);

        if (strcmp(msg.mtext, "bye") == 0)
        {
            pthread_mutex_lock(&tid_mutex);
            if (recv_tid != 0)
                pthread_cancel(recv_tid);
            pthread_mutex_unlock(&tid_mutex);
            break;
        }
    }
    return NULL;
}

void *receiver_thread(void *arg)
{
    int msgid = *((int *)arg);
    pthread_mutex_lock(&tid_mutex);
    recv_tid = pthread_self();
    pthread_mutex_unlock(&tid_mutex);

    while (1)
    {
        msg_t msg;
        msgrcv(msgid, &msg, sizeof(msg.mtext), 1, 0); 

        printf("Received: %s\n", msg.mtext);

        if (strcmp(msg.mtext, "bye") == 0)
        {
            pthread_mutex_lock(&tid_mutex);
            if (send_tid != 0)
                pthread_cancel(send_tid);
            pthread_mutex_unlock(&tid_mutex);
            break;
        }
    }
    return NULL;
}

int main(int argc, char **argv)
{
    int msgid = msgget((key_t)0x00000005, IPC_CREAT | 0600);
    if (msgid == -1)
    {
        perror("msgget");
        return 1;
    }

    pthread_t s_tid, r_tid;
    pthread_create(&s_tid, NULL, sender_thread, &msgid);
    pthread_create(&r_tid, NULL, receiver_thread, &msgid);

    pthread_join(s_tid, NULL);
    pthread_join(r_tid, NULL);

    msgctl(msgid, IPC_RMID, NULL); 
    return 0;
}