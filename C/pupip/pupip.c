#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

char msg[] = "GET / HTTP/1.0\r\nHost: ifconfig.me\r\n\r\n";

int main()
{
        int sock, ret;
        int bytes;
        struct addrinfo *res;
        struct addrinfo hints;
        char buf[BUFSIZ];

        memset(&hints, 0, sizeof(hints));

        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;

        ret = getaddrinfo("ifconfig.me", "80", &hints, &res);
        if (ret != 0) {
                printf("getaddrinfo(): %s", gai_strerror(ret));
                exit(EXIT_FAILURE);
        }

        sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (sock == -1) {
                perror("socket()");
                exit(EXIT_FAILURE);
        }

        ret = connect(sock, res->ai_addr, res->ai_addrlen);
        if (ret == -1) {
                perror("connect()");
                exit(EXIT_FAILURE);
        }
        freeaddrinfo(res);

        bytes = send(sock, msg, sizeof(msg), 0);
        if (bytes == -1) {
                perror("send()");
                exit(EXIT_FAILURE);
        }

        while ((bytes = recv(sock, buf, BUFSIZ, 0)) != 0) {
                if (bytes == -1) {
                        perror("recv");
                        continue;
                }

                printf("%s\n", buf);
        }

        close(sock);
        return 0;
}
