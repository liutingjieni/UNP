/*************************************************************************
	> File Name: udp_ser.c
	> Author:jieni 
	> Mail: 
	> Created Time: 2019年12月13日 星期五 21时43分01秒
 ************************************************************************/

#include <stdio.h>
#include<sys/socket.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#define SERV_PORT 8888
#define MAXLINE 20

void dg_echo(int sockfd, struct sockaddr* pcliaddr, socklen_t clilen)
{
    int n;
    socklen_t len;
    char mesg[MAXLINE];

    while (1) {
        len = clilen;
        n = recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len);
        sendto(sockfd, mesg, n, 0, pcliaddr, len);
    }
}

static int count;
static void recvfrom_int(int signo)
{
    printf("\nrecvived %d datagrams\n", count);
    exit(0);
}

void dg_echo_02(int sockfd, struct sockaddr* pcliaddr, socklen_t clilen)
{
    socklen_t len;
    char mesg[MAXLINE];
    int n = 30 * 1400;
    signal(SIGINT, recvfrom_int);

    setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &n, sizeof(n));
    while (1) {
        len = clilen;
        recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len);

        count++;
    }
}


int main()
{
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    
    sockfd = socket(AF_INET, SOCK_DGRAM, 0); //SOCK_DGRAM 创建UDP套接字

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family =  AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    dg_echo_02(sockfd, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
}
