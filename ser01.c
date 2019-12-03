/*************************************************************************
	> File Name: ser01.c
	> Author: 
	> Mail: 
	> Created Time: 2019年12月03日 星期二 22时35分15秒
 ************************************************************************/

#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#define SERV_PORT 8888
#define MAXLINE 20
#define LISTENQ 1000
void str_echo(int sock_fd)
{
    ssize_t n;
    char buf[MAXLINE];
    n = read(sock_fd, buf, MAXLINE);
    write(sock_fd, buf, n);
}

int main()
{
    int listen_fd, conn_fd;
    pid_t child_pid;
    socklen_t cli_len;
    struct sockaddr_in cli_addr, serv_addr;

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&serv_addr, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(SERV_PORT);

    bind(listen_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    listen(listen_fd, LISTENQ);

    while(1) {
        cli_len = sizeof(cli_addr);
        conn_fd = accept(listen_fd, (struct sockaddr *)&serv_addr, &cli_len);

        if ((child_pid == fork()) == 0) {
            close(listen_fd);
            str_echo(conn_fd);
            exit(0);
        }
        close(conn_fd);
    } 
}
