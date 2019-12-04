/*************************************************************************
	> File Name: cli01.c
	> Author: 
	> Mail: 
	> Created Time: 2019年12月03日 星期二 22时51分14秒
 ************************************************************************/

#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<string.h>
#define MAXLINE 20
#define SERV_PORT 8888

void str_cli(int sock_fd)
{
    char sendline[MAXLINE], recvline[MAXLINE];

    while (scanf("%s", sendline) != 0) {
        printf("^^^^^^^^^^^\n");
        if (send(sock_fd, sendline, strlen(sendline), 0) < 0) {
            printf("send\n");
        }
        printf("sendline = %s\n",sendline);

        if (recv(sock_fd, recvline, MAXLINE, 0) == 0) {

        }
        printf("recvline = %s\n", recvline);
        bzero(sendline, MAXLINE);
        bzero(recvline, MAXLINE);

    }
}

int main(int argc, char *argv[])
{
    int sock_fd;
    struct sockaddr_in serv_addr;

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&serv_addr, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);

    inet_pton(AF_INET, argv[1], &serv_addr.sin_addr);

    connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    str_cli(sock_fd);
    exit(0);


}
