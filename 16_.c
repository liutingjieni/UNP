/*************************************************************************
	> File Name: 16_.c
	> Author:jieni 
	> Mail: 
	> Created Time: 2020年04月02日 星期四 22时40分54秒
 ************************************************************************/

#include <stdio.h>

int connect_nonb(int sockfd, const SA *saptr, socklen_t salen, int nsec)
{
    int flags, n, error;
    socklen_t len;
    fd_set rset, wset;
    struct timeval tval;

    flags = fcntl(sockfd, F_GETEL, 0);
    fcntl(sockfd, F_SETFL, flsgs | O_NONBLOCK);

    errno = 0 ;
    if ( (n = connect(sockfd, saptr, salen)) < 0 ) {
        if (errno != EINPROGRESS) {
            return -1;
        }
    }

    if (n == 0) {
        goto done;
    }

    FD_ZERO(&rset);
    FD__SET(sockfd, &rset);
    west = rset;
    tval.tv_sec= nsec;
    tval.tv_usec = 0;

    if ((n = select(sockfd + 1, &rset, &wset, NULL, nsec ? &tval : NULL)) == 0) {
        close(sockfd);
        errno = ETIMEDOUT;
        return -1;
    }

    if (FD_ISSET(sockfd, &rset) || FD_ISSET(sockfd, &wset)) {
        len = sizeof(error);
        if (getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, &len) < 0) {
            return -1;
        }
    }
    else {
        err_quit("select error: sockfd not set");
    }
done:
    fcntl(sockfd, F_SETFL, flags);

    if (error) {
        close(sockfd);
        errno = error;
        return -1;
    }
    return 0;
}
