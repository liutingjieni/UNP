/*************************************************************************
	> File Name: ser01.c
	> Author: 
	> Mail: 
	> Created Time: 2019年12月03日 星期二 22时35分15秒
 ************************************************************************/

#include<stdio.h>
#include<sys/socket.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#define SERV_PORT 8888
#define MAXLINE 20
#define LISTENQ 1000


void sig_chld(int signo)
{
    pid_t pid;
    int stat;

    printf("&&&&&&&&&&&&&&&&&&&&\n");
    while ((pid = waitpid(-1, &stat, WNOHANG)) > 0) {
        printf("child %d terminated\n", pid);
    }
    return;
}
void str_echo(int sock_fd)
{
    while(1) {
        ssize_t n;
        char buf[MAXLINE];
        bzero(buf, MAXLINE);
        printf("1 = %s\n", buf);
        n = recv(sock_fd, buf, MAXLINE, 0);
        if (n == 0 || n < 0) { 
            exit(0);
        }
        printf("2 = %s %d\n", buf, n); 
        send(sock_fd, buf, n, 0);
        printf("3 = %s\n", buf);
    }
}

int main()
{
    int listen_fd, conn_fd;
    pid_t child_pid;
    socklen_t cli_len;
    struct sockaddr_in cli_addr, serv_addr;

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    signal(SIGCHLD, sig_chld);
    bzero(&serv_addr, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(SERV_PORT);

    bind(listen_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    listen(listen_fd, LISTENQ);
    while(1) {
        printf("*****************\n");
        cli_len = sizeof(cli_addr);
        conn_fd = accept(listen_fd, (struct sockaddr *)&serv_addr, &cli_len);

        if ((child_pid = fork()) == 0) {
            printf("lalaal\n");
            close(listen_fd);
            str_echo(conn_fd);
            exit(0);
        }
        close(conn_fd);
    } 
}
