// 利用命名管道实现一个进程向另一个进程转存文件内容的功能
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_PATH "/tmp/fifo"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage %s Filename", argv[0]);
        return 1;
    }

    if (-1 == access(FIFO_PATH, F_OK))
    {
        if (-1 == mkfifo(FIFO_PATH, 0600))
        {
            perror("mkfifo");
            return -1;
        }
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        perror("fopen");
        return -1;
    }

    int fd = open(FIFO_PATH, O_WRONLY);
    if (fd == -1)
    {
        perror("open");
        fclose(fp);
        return -1;
    }
    
    char buf[1024];
    size_t n;
    while ((n = fread(buf, 1, sizeof(buf) - 1, fp)) > 0)
    {
        if (write(fd, buf, n) != (ssize_t)n)
        {
            perror("write");
            break;
        }
    }

    fclose(fp);
    close(fd);
    printf("写进程退出了\n");
    return 0;
}