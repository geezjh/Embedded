#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef  struct sockaddr       sa_t;
typedef  struct sockaddr_in    sin_t;

int main(int argc,char** argv)
{
    if(argc < 2)
    {
        fprintf(stderr,"Usage %s bcastPort\n",argv[0]);
        return -1;
    }
    /*1. 创建数据报套接字*/
    int sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd == -1)
    {
        perror("socket");
        return -1;
    }
    /*2.设置套接字的广播属性*/
    int enable  = 1;
    if(-1 == setsockopt(sockfd,SOL_SOCKET,SO_BROADCAST,&enable,sizeof(int)))
    {
         perror("setsockopt");
         close(sockfd);
         return -1;
    }
    /*3.指定广播地址和广播端口*/
    sin_t  mcast          =  {AF_INET};
    mcast.sin_port        =  htons(atoi(argv[1]));
    mcast.sin_addr.s_addr =  htonl(INADDR_BROADCAST);
    int  len  = sizeof(sin_t);

    /*4.发送广播数据到广播地址和广播端口 */
    char buf[64] = {0};
    printf("通知:");
    fgets(buf,sizeof(buf),stdin);
    sendto(sockfd,buf,strlen(buf),0,(sa_t*)&mcast,len);

    while(1)
    {
        /*5. 接收回复网络数据*/
        char buf[64] = {0};
        sin_t  peer          =  {0};
        recvfrom(sockfd,buf,sizeof(buf)-1,0,(sa_t*)&peer,&len);
        printf("[%s:%d]回复数据:%s\n",inet_ntoa(peer.sin_addr), ntohs(peer.sin_port),buf);
    }

    /*6.关闭套接字 */
    close(sockfd);
    return 0;
}
 