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
    /*2.绑定任一地址和广播端口*/
    sin_t  any          =  {AF_INET};
    any.sin_port        =  htons(atoi(argv[1]));
    any.sin_addr.s_addr =  htonl(INADDR_ANY);
    int  len  = sizeof(sin_t);
    if (-1 == bind(sockfd,(sa_t*)&any,len))
    {
        perror("bind");
        close(sockfd);
        return -1;
    }
     /*3. 接收广播数据*/
    char buf[64] = {0};
    sin_t  peer          =  {0};
    recvfrom(sockfd,buf,sizeof(buf)-1,0,(sa_t*)&peer,&len);
    printf("[%s:%d]回复数据:%s\n",inet_ntoa(peer.sin_addr), ntohs(peer.sin_port),buf);

    /*4.回复数据 */
    const char* p  = "😀😀收到";
    sendto(sockfd,p,strlen(p),0,(sa_t*)&peer,len);  

    /*5.关闭套接字 */
    close(sockfd);
    return 0;
}
 