/* 利用UDP协议完成文件传送功能，实现文件下载。
提示：先发送文件大小(假定4字节数据)，下载文件的
网络程序要根据获取到的文件大小，作为接收网络数据终止的条件。 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>

typedef struct sockaddr sa_t;
typedef struct sockaddr_in sin_t;
#define BUF_SIZE 1024
#define SERVER_IP "127.0.0.1"
#define PORT 12345

int main(int argc, char **argv)
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1)
    {
        perror("socket");
        return -1;
    }
    sin_t client = {AF_INET};
    client.sin_addr.s_addr = inet_addr(SERVER_IP);
    client.sin_port = htons(PORT);
    int len = sizeof(sin_t);
    char buf[BUF_SIZE] = {0};
    uint32_t file_size;

    printf("请输入你想下载的文件名：");
    scanf("%s", buf);

    sendto(sockfd, buf, strlen(buf), 0, (sa_t *)&client, len);

    recvfrom(sockfd, &file_size, sizeof(file_size), 0, (sa_t *)&client, &len);
    file_size = ntohl(file_size); 

    printf("文件大小是:%u \n", file_size);

    FILE *fp = fopen("download_file", "wb");
    if (fp == NULL)
    {
        perror("fopen");
        close(sockfd);
        return -1;
    }

    long sum_recv = 0;
    size_t b_recv;
    while (sum_recv < file_size)
    {
        b_recv = recvfrom(sockfd, buf, sizeof(buf) - 1, 0, (sa_t *)&client, &len);
        fwrite(buf, 1, b_recv, fp);
        sum_recv += b_recv;
    }

    fclose(fp);
    close(sockfd);
    printf("文件下载完毕.....\n");
    return 0;
}