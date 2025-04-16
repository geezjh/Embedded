#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

typedef struct sockaddr sa_t;
typedef struct sockaddr_in sin_t;

int main(int argc, char **argv)
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    sin_t server_addr = {AF_INET};
    server_addr.sin_port = htons(8888);
    server_addr.sin_addr.s_addr = inet_addr("192.168.13.91");

    char buf[1024];
    socklen_t len = sizeof(sin_t);

    while (1)
    {
        printf("== == == == ==\n");
        printf("1. 加入群聊\n");
        printf("2. 离开群聊\n");
        printf("3. 查看群成员\n");
        printf("4. 退出程序\n");
        printf("== == == == ==\n");
        printf("请输入选项：");

        int choice;
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
        {
            struct ip_mreq mreq;
            mreq.imr_multiaddr.s_addr = inet_addr("224.0.2.100");
            mreq.imr_interface.s_addr = INADDR_ANY;
            if (setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0)
            {
                perror("加入多播组失败");
                break;
            }
            sendto(sockfd, "已加群", strlen("已加群"), 0, (sa_t *)&server_addr, sizeof(server_addr));
            break;
        }
        case 2:
        {
            struct ip_mreq mreq;
            mreq.imr_multiaddr.s_addr = inet_addr("224.0.2.100");
            mreq.imr_interface.s_addr = INADDR_ANY;
            if (setsockopt(sockfd, IPPROTO_IP, IP_DROP_MEMBERSHIP, &mreq, sizeof(mreq)) < 0)
            {
                perror("离开多播组失败");
                break;
            }
            sendto(sockfd, "已离群", strlen("已离群"), 0, (sa_t *)&server_addr, sizeof(server_addr));
            break;
        }

        // 修改选项3的接收逻辑，验证来源地址
        case 3:
        {
            sendto(sockfd, "查看群成员", strlen("查看群成员"), 0, (sa_t *)&server_addr, sizeof(server_addr));
            sin_t from_addr;
            socklen_t from_len = sizeof(from_addr);
            ssize_t n = recvfrom(sockfd, buf, sizeof(buf), 0, (sa_t *)&from_addr, &from_len);
            // 验证是否为服务器的响应
            if (n > 0 && from_addr.sin_addr.s_addr == server_addr.sin_addr.s_addr &&
                from_addr.sin_port == server_addr.sin_port)
            {
                printf("群成员列表：\n%s", buf);
            }
            else
            {
                printf("接收群成员列表失败\n");
            }
            break;
        }
        case 4:
            close(sockfd);
            return 0;
        default:
            printf("输入的选项有误，请重新输入\n");
            break;
        }

        // 接收广播消息
        if (recvfrom(sockfd, buf, sizeof(buf), MSG_DONTWAIT, NULL, NULL) > 0)
        {
            printf("广播消息：%s\n", buf);
        }
    }
}