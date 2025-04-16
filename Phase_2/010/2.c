/* 创建子进程，父进程等待子进程退出，
如果在10s 中子进程仍然还未退出，
父进程强制子进程退出。
提示： 使用定时器， */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

pid_t pid;

void handler(int s)
{
    if (pid > 0)
    {
        kill(pid, SIGKILL);
    }
}

int main(int argc, char **argv)
{
    signal(SIGALRM, handler);

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        exit(1);
    }
    if (pid == 0)
    {
        while (1)
        {
            printf("This is son.\n");
            sleep(1);
        }
    }
    else
    {
        alarm(10);
        wait(NULL);
    }

    return 0;
}