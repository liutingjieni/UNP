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

void str_cli(FILE *fp, int sock_fd)
{
    char sendline[MAXLINE], recvline[MAXLINE];

    while (fgets(sendline, MAXLINE, fp) != NULL) {
        write(sock_fd, sendline, strlen(sendline));

        if (readline(sock_fd, recvline, MAXLINE) == 0) {

        }
        fputs(recvline, stdout);
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

    Inet_pton(AF_INET, argv[1], &serv_addr.sin_addr);

    connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    str_cli(stdin, sock_fd);
    exit(0);

}
