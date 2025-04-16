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
#define PORT 12345

int main(int argc, char **argv)
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1)
    {
        perror("socket");
        return -1;
    }
    sin_t server = {AF_INET};
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);
    int len = sizeof(sin_t);
    if (bind(sockfd, (sa_t *)&server, len) == -1)
    {
        perror("bind");
        close(sockfd);
        return -1;
    }
    char buf[BUF_SIZE] = {0};
    sin_t peer;
    recvfrom(sockfd, buf, sizeof(buf) - 1, 0, (sa_t *)&peer, &len);
    printf("下载的文件名是:%s\n", buf);

    FILE *fp = fopen(buf, "rb");
    if (fp == NULL)
    {
        perror("fopen");
        close(sockfd);
        return -1;
    }

    fseek(fp, 0, SEEK_END);
    uint32_t file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    file_size = htonl(file_size); 
    sendto(sockfd, &file_size, sizeof(file_size), 0, (sa_t *)&peer, len);
    size_t b_read = 0;
    while ((b_read = fread(buf, 1, BUF_SIZE, fp)) > 0)
    {
        sendto(sockfd, buf, b_read, 0, (sa_t *)&peer, len);
    }

    fclose(fp);
    close(sockfd);
    return 0;
}