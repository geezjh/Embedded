/* 1. 创建不相关的两个进程(P1,P2),要求，
P1 将自身的PID 写入命名管道，P2 从命名管道中获取P1的PID，
P2 向 P1 发送携带数据的信号 SIGUSR1，P1 接收到信号后，
获取传递的数据，在数据指定的秒数过后退出。 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdbool.h>

#define FIFO_PATH "/tmp/fifo"

void sigHandler(int s, siginfo_t *info, void *argp)
{
    int sigval = info->si_int;
    alarm(sigval);
}

int main(int argc, char **argv)
{
    if (-1 == access(FIFO_PATH, F_OK))
    {
        if (-1 == mkfifo(FIFO_PATH, 0600))
        {
            perror("mkfifo");
            return -1;
        }
    }

    const struct sigaction act = {
        .sa_sigaction = sigHandler,
        .sa_flags = SA_SIGINFO,
    };

    if (-1 == sigaction(SIGUSR1, &act, NULL))
    {
        perror("sigaction");
        return -1;
    }

    int fd = open(FIFO_PATH, O_WRONLY);
    if (fd == -1)
    {
        perror("open");
        return -1;
    }

    pid_t pid = getpid();
    write(fd, &pid, sizeof(pid_t));
    close(fd);
    while (1)
    {
        pause();
    }
    return 0;
}