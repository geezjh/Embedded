#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

typedef struct sockaddr sa_t;
typedef struct sockaddr_in sin_t;
typedef struct ClientNode
{
    sin_t client_addr;
    struct ClientNode *next;
} ClientNode;

// 链表头指针
ClientNode *client_list = NULL;

// 添加客户端到链表
void add_client(sin_t client_addr)
{
    ClientNode *new_node = (ClientNode *)malloc(sizeof(ClientNode));
    if (new_node == NULL)
    {
        perror("malloc");
        return;
    }
    new_node->client_addr = client_addr;
    new_node->next = client_list;
    client_list = new_node;
}

// 从链表中移除客户端
void remove_client(sin_t client_addr)
{
    ClientNode *p = client_list;
    ClientNode *q = NULL;

    while (p)
    {
        if (p->client_addr.sin_addr.s_addr == client_addr.sin_addr.s_addr && p->client_addr.sin_port == client_addr.sin_port)
        {
            if (q == NULL)
                client_list = p->next;
            else
                q->next = p->next;
            free(p);
            return;
        }
        q = p;
        p = p->next;
    }
}

// 释放链表内存
void free_client_list()
{
    ClientNode *p = client_list;
    ClientNode *temp;
    while (p)
    {
        temp = p;
        p = p->next;
        free(temp);
    }
    client_list = NULL;
}

// 广播消息到群组
void broadcast_message(int sockfd, const char *message, sin_t group_addr)
{
    if (sendto(sockfd, message, strlen(message), 0, (sa_t *)&group_addr, sizeof(group_addr)) < 0)
    {
        perror("sendto");
    }
}

// 查看群成员并发送给客户端
void send_client_list(int sockfd, sin_t client_addr)
{
    char buf[1024] = {0};
    ClientNode *p = client_list;
    size_t remaining = sizeof(buf);
    char *ptr = buf;

    while (p && remaining > 1)
    {
        int written = snprintf(ptr, remaining, "%s:%d\n",
                               inet_ntoa(p->client_addr.sin_addr),
                               ntohs(p->client_addr.sin_port));
        if (written < 0 || written >= remaining)
            break;
        ptr += written;
        remaining -= written;
        p = p->next;
    }
    sendto(sockfd, buf, strlen(buf), 0, (sa_t *)&client_addr, sizeof(client_addr));
}

int main(int argc, char **argv)
{
    sin_t server_addr = {AF_INET}, client_addr;
    socklen_t len = sizeof(sin_t);
    char buf[1024] = {0};
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_port = htons(8888);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (sa_t *)&server_addr, len) < 0)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    sin_t group_addr = {AF_INET};
    group_addr.sin_port = htons(8888);
    group_addr.sin_addr.s_addr = inet_addr("224.0.2.100");

    struct in_addr local_interface;
    local_interface.s_addr = htonl(INADDR_ANY);
    if (setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_IF, &local_interface, sizeof(local_interface)) < 0)
    {
        perror("设置多播接口失败");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        bzero(buf, sizeof(buf));
        recvfrom(sockfd, buf, sizeof(buf), 0, (sa_t *)&client_addr, &len);
        printf("%s\n",buf);
        if (strcmp(buf, "已加群") == 0)
        {
            add_client(client_addr);
            char msg[1024];
            sprintf(msg, "%s:%d 已加群", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
            broadcast_message(sockfd, msg, group_addr);
        }
        else if (strcmp(buf, "已离群") == 0)
        {
            remove_client(client_addr);
            char msg[1024];
            sprintf(msg, "%s:%d 已离群", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
            broadcast_message(sockfd, msg, group_addr);
        }
        else if (strcmp(buf, "查看群成员") == 0)
            send_client_list(sockfd, client_addr);
    }

    free_client_list();
    close(sockfd);
    return 0;
}