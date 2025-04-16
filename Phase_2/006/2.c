#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char **argv)
{
    int fd[2];
    char buffer[1];
    ssize_t n = 0;
    int max = 0;

    if (pipe(fd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // 将写管道设置为非阻塞模式
    int flags = fcntl(fd[1], F_GETFL, 0);
    if (flags == -1)
    {
        perror("fcntl F_GETFL");
        exit(EXIT_FAILURE);
    }

    if (fcntl(fd[1], F_SETFL, flags | O_NONBLOCK) == -1)
    {
        perror("fcntl F_SETFL");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        n = write(fd[1], buffer, sizeof(buffer));
        if (n == -1)
        {
            if (errno == EAGAIN || errno == EWOULDBLOCK)
                break;
            else
            {
                perror("write");
                exit(EXIT_FAILURE);
            }
        }
        max += n;
    }

    close(fd[0]);
    close(fd[1]);

    printf("默认管道容量大约为: %d 字节\n", max);
    return 0;
}
