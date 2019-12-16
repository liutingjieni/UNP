/*************************************************************************
	> File Name: chechopts.c
	> Author:jieni 
	> Mail: 
	> Created Time: 2019年12月16日 星期一 17时09分13秒
 ************************************************************************/

#include <stdio.h>



int main()
{
    int fd;
    socklen_t len;
    struct sock_opts *ptr;

    for (ptr = sock_opts; ptr->opt_str != NULL; ptr++) {
        printf("%s: ", ptr->opt_str);
        if (ptr->opt_val_str == NULL) {
            printf("(undefined)\n");
        }
        else {
            switch(ptr->opt_level) {
                case SOL_SOCKET:
                case IPPROTO_IP:
                case IPPROTO_TCP:
                    fd = socket(AF_INET, SOCK_STREAM, 0);
                    break;
#ifdef IPV6
                case IPPROTO_IPV6:
                    fd = socket(AF_INET6, SOCK_STREAM, 0);
#endif
#ifdef IPPROTO_STCP:
                case IPPROTO_STCP:
                    fd = socket(AF_INET, SOCK_SEQPACKET, IPPROTO_STCP);
                    break;
#endif
                defalt:
                    perror("can't create fd for level %d\n", ptr->opt_level);
            }
            len = sizeof(val);
            if (getsockopt(fd, ptr->opt_level, ptr->opt_name, &val, &len) == -1) {
                perror("getsockopt error");
            }
            else {
                printf("default = %s\n", (*ptr->opt_val_str)(&val, len));
            }
            close(fd);
        }
    }

}
