/* 创建2个线程，要求一个线程(A)获取文件大小并返回
，另一个线程(B)获取文件拥有者用户的权限并返回，
主线程等待两个线程的结果数据后，进行结果输出展示。(文件路径由主线程提供) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>

void *FileSize(void *argp)
{
    size_t *filesz = (size_t *)malloc(sizeof(size_t));
    struct stat status = {0};
    if (stat((char *)argp, &status) == -1)
    {
        perror("stat");
        *filesz = -1;
        return filesz;
    }
    *filesz = status.st_size;
    pthread_exit(filesz);
}

void *FilePm(void *argp)
{
    mode_t *filepm = (mode_t *)malloc(sizeof(mode_t));
    struct stat status = {0};
    if (stat((char *)argp, &status) == -1)
    {
        perror("stat");
        *filepm = -1;
        return filepm;
    }
    *filepm = status.st_mode;
    pthread_exit(filepm);
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage %s FilePath.\n", argv[0]);
        return 1;
    }

    pthread_t tid1, tid2;
    int error;
    if (error = pthread_create(&tid1, NULL, FileSize, argv[1]))
    {
        fprintf(stderr, "错误：%s\n", strerror(error));
        return 1;
    }

    if (error = pthread_create(&tid2, NULL, FilePm, argv[1]))
    {
        fprintf(stderr, "错误：%s\n", strerror(error));
        return 1;
    }

    printf("main thread\n");
    size_t *p = NULL;
    pthread_join(tid1, (void **)&p);
    mode_t *q = NULL;
    pthread_join(tid2, (void **)&q);

    printf("线程(A)获取文件大小:%ld\n", *p);
    printf("线程(B)获取文件拥有者用户的权限:%d\n", *q & 07777);

    free(p);
    free(q);
}
