#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct sockaddr sa_t;
typedef struct sockaddr_in sin_t;

int main(int argc, char **argv)
{
    /*1.创建数据报套接字*/
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1)
    {
        perror("socket");
        return -1;
    }
    /*2绑定服务器地址信息到套接字*/
    puts("socket create success!!");
    int len = sizeof(sin_t);

    char buf[64] = {0};
    sin_t peer = {0};
    peer.sin_port = htons(10086);
    peer.sin_addr.s_addr = inet_addr("192.168.13.183");
    /*4.发送数据给客户端*/
    const char *p = {"我有煜煜症"};
    sendto(sockfd, p, strlen(p), 0, (sa_t *)&peer, len);
    len = sizeof(sin_t);
    int n = recvfrom(sockfd, buf, sizeof(buf) - 1, 0, NULL, NULL);
    buf[n] = 0;
    printf("[%s:%d]发来数据:%s\n", inet_ntoa(peer.sin_addr), ntohs(peer.sin_port), buf);

    /*5.关闭套接字*/
    close(sockfd);
    return 0;
}