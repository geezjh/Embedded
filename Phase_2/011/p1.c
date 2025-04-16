/* 两个没有亲缘关系的进程之间通过消息队列实现简单的聊天,要求在每个进程中创建2个线程，
分别实现消息的发送与接收，同时，一旦一个线程退出，就取消另一个线程。（例如：接收数据
的线程收到“bye”后，向发送数据线程发送取消请求后退出，
或发送数据线程发送“bye”数据后，向接收数据的线程发送取消请求后，退出） */
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
        msg.type = 1;
        fgets(msg.mtext, sizeof(msg.mtext), stdin);
        strtok(msg.mtext, "\n"); 

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
        msgrcv(msgid, &msg, sizeof(msg.mtext), 2, 0);

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