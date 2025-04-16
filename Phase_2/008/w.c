#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
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

    int semid, shmid;
    char *shmaddr;

    // 打开信号量
    semid = mysem_open(SEM_KEY, 1);
    if (semid == -1)
    {
        perror("semget");
        return -1;
    }

    // 初始化信号量
    if (mysem_initvalue(semid, 0, 1) == -1)
    {
        perror("semctl");
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

    // 打开文件
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        return -1;
    }

    // 获取文件大小
    struct stat st;
    if (fstat(fd, &st) == -1)
    {
        perror("fstat");
        close(fd);
        return -1;
    }
    size_t file_size = st.st_size;

    // 写入文件大小到共享内存
    memcpy(shmaddr, &file_size, sizeof(size_t));

    size_t bytes_written = 0;
    while (bytes_written < file_size)
    {
        // P操作，获取信号量
        if (mysem_p(semid, 0) == -1)
        {
            perror("semop");
            close(fd);
            return -1;
        }

        size_t to_write = (file_size - bytes_written > SHM_SIZE - sizeof(size_t))
                              ? SHM_SIZE - sizeof(size_t)
                              : file_size - bytes_written;
        ssize_t n = read(fd, shmaddr + sizeof(size_t), to_write);
        if (n == -1)
        {
            perror("read");
            close(fd);
            return -1;
        }

        bytes_written += n;

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
