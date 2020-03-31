/*************************************************************************
	> File Name: 16_2_strclinonb.c
	> Author:jieni 
	> Mail: 
	> Created Time: 2020年03月31日 星期二 23时45分13秒
 ************************************************************************/

#include <stdio.h>

void str_cli(FILE *fp, int sockfd)
{
    int maxfdpl, val, stdineof;
    ssize_t n, nwrutten;
    fd_set rset, wset;
    char to[MAXLINE], fr[MAXLINE];
    char *toiptr, *tooptr, *friptr, *froptr;

    val = fcntl(sockfd, F_GETFL, 0);
    fcntl(sockfd, F_SETFL, val | O_NONBLOCK);

    val = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, val | O_NONBLOCK);

    toiptr = tooptr = to;
    friptr = froptr = fr;
    stdineof = 0;

    maxfdpl = max(max(STDIN_FILENO, STDOUT_FILENO), sockfd) + 1;
    for(;;) {
        FD_ZERO(&rset);
        FD_ZERO(&wset);
        if (stdineof == 0 && toiptr < &to[MAXLINE]) {
            FD_SET(STDIN_FILENO, &rset);
        }
        if (friptr < &fr[MAXLINE]) {
            FD_SET(sockfd, &rset);
        }
        if (tooptr != toiptr) {
            FD_SET(sockfd, &wset);
        }
        if (froptr != friptr) {
            FD_SET(STDOUT_FILENO, &wset);
        }
        select(maxfdpl, &rset, &wset, NULL, NULL);
    }
}
