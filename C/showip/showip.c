/* domain to ip translation */
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
        int ret;
        struct addrinfo *res, *p;

        if (argc < 2) {
                fprintf(stderr, "%s <domain_name>\n", argv[0]);
                exit(EXIT_FAILURE);
        }

        ret = getaddrinfo(argv[1], NULL, NULL, &res);
        if (ret != 0) {
                fprintf(stderr, "getaddrinfo(): %s\n", gai_strerror(ret));
                exit(EXIT_FAILURE);
        }

        char buf[INET6_ADDRSTRLEN];
        for (p = res; p != NULL; p = p->ai_next) {
                if (p->ai_family == AF_INET) {
                        struct sockaddr_in *ipv4 = (struct sockaddr_in*)p->ai_addr;
                        inet_ntop(AF_INET, &(ipv4->sin_addr), buf, p->ai_addrlen);
                } else {
                        struct sockaddr_in6 *ipv6 = (struct sockaddr_in6*)p->ai_addr;
                        inet_ntop(AF_INET6, &(ipv6->sin6_addr), buf, p->ai_addrlen);
                }

                printf("%s\n", buf);
        }

        freeaddrinfo(res);
}
