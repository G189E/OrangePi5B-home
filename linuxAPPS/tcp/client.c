#include <sys/types.h>  
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>

/*
 *socket
 *connect
 *send
*/
#define TCP_PORT 8080
int main(int argc,char **argv)
{
    if(2 != argc){
        printf("invaild usage:\n    %s <IPADDRESS>\n",argv[0]);
        exit(EXIT_FAILURE);
    }
    unsigned char tcpBuffer[1024];
    int socfd;
    struct sockaddr_in tcpaddr;
    socfd = socket(AF_INET,SOCK_STREAM,0);
    if(0 == inet_aton(argv[1],&tcpaddr.sin_addr)){
        printf("invalid ipaddr\n");
        exit(EXIT_FAILURE);
    }
    tcpaddr.sin_family = AF_INET;
    tcpaddr.sin_port = htons(TCP_PORT);
    memset(tcpaddr.sin_zero,0,8);
    int conret = connect(socfd,(const struct sockaddr *)&tcpaddr,sizeof(tcpaddr));
    if(-1 == conret){
        perror("connect error");
        exit(EXIT_FAILURE);
    }
    while (1)
    {
        if(fgets(tcpBuffer,1024,stdin)){
            send(socfd,tcpBuffer,strlen(tcpBuffer),0);
            memset(tcpBuffer,0,1024);
        }

    }
    
}