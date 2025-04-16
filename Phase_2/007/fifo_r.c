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

    int fd = open(FIFO_PATH, O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        return -1;
    }

    FILE *fp = fopen(argv[1], "w");
    if (fp == NULL)
    {
        perror("fopen");
        close(fd);
        return -1;
    }

    char buf[1024];
    size_t n;
    while ((n = read(fd, buf, sizeof(buf) - 1)) > 0)
    {
        if (fwrite(buf, 1, n, fp) != n)
        {
            perror("fwrite");
            break;
        }
    }

    fclose(fp);
    close(fd);
    unlink(FIFO_PATH);
    printf("读进程退出了\n");
    return 0;
}