/* 1. 创建一个进程，在进程中启动另一个进程，要求启动进程同时
向其传递一个数据，被启动的进程根据传递的参数不同取值实现
不同的操作，分别实现当传递的数据为ls，输出当前目录下的内容，
传递rm，实现删除当前目录下名为a.out 的文件 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char **argv)
{

    if (argc != 2)
    {
        fprintf(stderr, "Usage %s command\n", argv[0]);
        return 1;
    }

    pid_t pid = vfork();
    if (pid < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid == 0)
    {
        if (strcmp(argv[1], "ls") == 0)
        {
            execl("/bin/ls", "ls", NULL);
            perror("execl");
            exit(1);
        }
        else if (strcmp(argv[1], "rm") == 0)
        {
            execl("/bin/rm", "rm", "a.out", NULL);
            perror("execl");
            exit(1);
        }
        else
        {
            fprintf(stderr, "Unknown command: %s\n", argv[1]);
            exit(1);
        }
    }
    else
    {
        wait(NULL);
    }

    return 0;
}