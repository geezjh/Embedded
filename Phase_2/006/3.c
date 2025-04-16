/* 父子进程分别实现对同一目录下的内容进行统计，
要求子进程统计子文件个数，父进程统计子目录个数，
并且分别将结果传递给对方进行输出； */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s directory\n", argv[0]);
        return 1;
    }
    
    int fd[2];
    int fd1[2];
    if (pipe(fd) == -1 || pipe(fd1) == -1)
    {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();
    int count_file = 0;
    int count_dir = 0;

    if (pid < 0)
    {
        perror("fork");
        return 1;
    }
    if (pid == 0)
    {
        close(fd[0]);
        close(fd1[1]);

        DIR *dir = opendir(argv[1]);
        if (dir == NULL)
        {
            perror("opendir");
            exit(EXIT_FAILURE);
        }

        struct dirent *p;
        while ((p = readdir(dir)) != NULL)
        {
            if (p->d_type == 8)
            {
                count_file++;
            }
        }
        closedir(dir);

        if (write(fd[1], &count_file, sizeof(count_file)) == -1)
        {
            perror("write");
            exit(EXIT_FAILURE);
        }
        close(fd[1]);

        if (read(fd1[0], &count_dir, sizeof(count_dir)) == -1)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }
        close(fd1[0]);

        printf("子进程统计的文件个数: %d\n", count_file);
        printf("从父进程接收的目录个数: %d\n", count_dir);

        exit(EXIT_SUCCESS);
    }
    else
    {
        close(fd[1]);
        close(fd1[0]);

        DIR *dir = opendir(argv[1]);
        if (dir == NULL)
        {
            perror("opendir");
            return 1;
        }

        struct dirent *p;
        while ((p = readdir(dir)) != NULL)
        {
            if (p->d_type == 4 && strcmp(p->d_name, ".") != 0 && strcmp(p->d_name, "..") != 0)
            {
                count_dir++;
            }
        }
        closedir(dir);

        if (write(fd1[1], &count_dir, sizeof(count_dir)) == -1)
        {
            perror("write");
            return 1;
        }
        close(fd1[1]);

        if (read(fd[0], &count_file, sizeof(count_file)) == -1)
        {
            perror("read");
            return 1;
        }
        close(fd[0]);

        printf("父进程统计的目录个数: %d\n", count_dir);
        printf("从子进程接收的文件个数: %d\n", count_file);

        wait(NULL);
    }
    return 0;
}