#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "mysem.h"

#define SEM_KEY 0x00000001
#define SHM_KEY 0x00000002
#define SHM_SIZE 1024

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage %s FileName\n", argv[0]);
        return -1;
    }

    int exist = 0;
    if (mysem_exist(SEM_KEY) == 0)
    {
        exist = 1;
    }

    int semid, shmid;
    char *shmaddr;

    // 打开信号量
    semid = mysem_open(SEM_KEY, 1);
    if (semid == -1)
    {
        perror("semget");
        return -1;
    }

    // 打开共享内存
    shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0600);
    if (shmid == -1)
    {
        perror("shmget");
        return -1;
    }

    // 连接共享内存
    shmaddr = (char *)shmat(shmid, NULL, 0);
    if (shmaddr == (char *)-1)
    {
        perror("shmat");
        return -1;
    }

    // 打开输出文件
    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd == -1)
    {
        perror("open");
        return -1;
    }

    // 读取文件大小
    size_t file_size;
    memcpy(&file_size, shmaddr, sizeof(size_t));

    size_t bytes_read = 0;
    while (bytes_read < file_size)
    {
        // P操作，获取信号量
        if (mysem_p(semid, 0) == -1)
        {
            perror("semop");
            close(fd);
            return -1;
        }

        size_t to_read = (file_size - bytes_read > SHM_SIZE - sizeof(size_t))
                             ? SHM_SIZE - sizeof(size_t)
                             : file_size - bytes_read;
        ssize_t n = write(fd, shmaddr + sizeof(size_t), to_read);
        if (n == -1)
        {
            perror("write");
            close(fd);
            return -1;
        }

        bytes_read += n;

        // V操作，释放信号量
        if (mysem_v(semid, 0) == -1)
        {
            perror("semop");
            close(fd);
            return -1;
        }
    }

    close(fd);

    // 分离共享内存
    if (shmdt(shmaddr) == -1)
    {
        perror("shmdt");
        return -1;
    }

    return 0;
}