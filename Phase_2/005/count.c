// 1.创建一个子进程,要求子进程对一个目录中的子目录或者文件进行
// 数量统计,并汇报给父进程,父进程将结果进行输出.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int count(const char *path)
{
    DIR *dir = opendir(path);
    if (dir == NULL)
    {
        perror("opendir");
        return -1;
    }

    struct dirent *p;
    int count = 0;

    while (p = readdir(dir))
    {
        if (strcmp(p->d_name, ".") != 0 && strcmp(p->d_name, ".."))
        {
            count++;
        }
    }

    closedir(dir);
    return count;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage %s directory", argv[0]);
        return -1;
    }

    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return -1;
    }

    if (pid == 0)
    {
        int N = count(argv[1]);
        if (-1 == N)
        {
            exit(EXIT_FAILURE);
        }
        exit(N);
    }
    else
    {
        int status;
        if (waitpid(pid, &status, 0) == -1)
        {
            perror("waitpid");
            return -1;
        }
        if (WIFEXITED(status))
        {
            int count = WEXITSTATUS(status);
            printf("输入的%s下有%d个子目录和文件\n", argv[1], count);
        }
    }
    return 0;
}