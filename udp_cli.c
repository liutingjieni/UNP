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

void dg_cli(FILE *fp, int sockfd, const struct sockaddr *pservaddr,
                                  socklen_t servlen)
{
    int n;
    char sendline[MAXLINE], recvline[MAXLINE+1];

    while (scanf("%s", sendline) != 0) {
        printf("%s\n", sendline);
        sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
        printf("%s\n", sendline);

        n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
        printf("%d\n", n);        
        recvline[n] = 0;
        printf("%s", recvline);

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
    servaddr.sin_port = htons(7);
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_port);
    
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    dg_cli(stdin, sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    exit(0);
}
