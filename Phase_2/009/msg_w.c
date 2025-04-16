#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <signal.h>

#define EXIT_MSG "EXIT"

typedef struct
{
    long type;
    pid_t pid;
    char mtext[1024];
} msg_t;

int msgid;

void handler(int signum)
{
    if (msgid != -1)
    {
        pid_t pid = getpid();
        msg_t msg = {1, pid, EXIT_MSG};
        msgsnd(msgid, &msg, sizeof(msg) - sizeof(long), 0);
    }
    exit(0);
}

int main(int argc, char **argv)
{
    signal(SIGINT, handler);

    msgid = msgget((key_t)0x00000005, IPC_CREAT | 0600);
    if (msgid == -1)
    {
        perror("msgget");
        return -1;
    }
    pid_t pid = getpid();
    printf("self id: %d\n", pid);

    while (1)
    {
        msg_t msg = {1, pid};
        printf("Please input your message (input 'EXIT' to quit): ");
        fgets(msg.mtext, sizeof(msg.mtext), stdin);
        msg.mtext[strcspn(msg.mtext, "\n")] = 0;

        if (strcmp(msg.mtext, EXIT_MSG) == 0)
        {
            msgsnd(msgid, &msg, sizeof(msg) - sizeof(long), 0);
            printf("You have exited. Recycling message queue...\n");
            msgctl(msgid, IPC_RMID, NULL);
            puts("回收队列!");
            break;
        }
        msgsnd(msgid, &msg, sizeof(msg) - sizeof(long), 0);

        bzero(&msg, sizeof(msg_t));
        msg.type = 2;
        size_t sz = msgrcv(msgid, &msg, sizeof(msg) - sizeof(long), 2, 0);
        if (sz == -1)
        {
            perror("msgrcv");
            continue;
        }
        if (strcmp(msg.mtext, EXIT_MSG) == 0)
        {
            printf("Peer %d has exited. Recycling message queue...\n", msg.pid);
            msgctl(msgid, IPC_RMID, NULL);
            puts("回收队列!");
            break;
        }
        printf("peer id:%d,peer text:%s\n", msg.pid, msg.mtext);
    }
    return 0;
}
