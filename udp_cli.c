/*************************************************************************
	> File Name: udp_cli.c
	> Author:jieni 
	> Mail: 
	> Created Time: 2019年12月13日 星期五 22时04分08秒
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

//未连接套接字
void dg_cli(FILE *fp, int sockfd, const struct sockaddr *pservaddr,
                                  socklen_t servlen)
{
    int n;
    char sendline[MAXLINE], recvline[MAXLINE+1];

    while (scanf("%s", sendline) != 0) {
        sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
        n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
        recvline[n] = 0;
        printf("%s\n", recvline);

    }
}
//已连接UDP套接字
int dg_cli_02(FILE *fp, int sockfd, const struct sockaddr *pservaddr, 
                                        socklen_t servlen)
{
    int n;
    char sendline[MAXLINE], recvline[MAXLINE + 1];

    if (connect(sockfd, (struct sockaddr *)pservaddr, servlen) < 0) {
        perror("connect");
    }
    while (fgets(sendline, MAXLINE, fp) != NULL) {
        write(sockfd, sendline, strlen(sendline));
         n  = read(sockfd, recvline, MAXLINE);
        recvline[n] = 0;
        fputs(recvline, stdout);
    }
}
#define NDG 2000
#define DGLEN 1400
//UDP缺乏流量控制
int dg_cli_03(FILE *fp, int sockfd, const struct sockaddr* pservaddr,
                                                socklen_t servlen)
{
    int i;
    char sendline[DGLEN];

    for (i = 0; i < NDG; i++) {
        sendto(sockfd, sendline, DGLEN, 0, pservaddr, servlen);
    }
}

int main(int argc, char *argv[2])
{
    int sockfd;
    struct sockaddr_in servaddr;

    if (argc != 2) {
        perror("no <IPaddress>");
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    dg_cli_03(stdin, sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    exit(0);
}
