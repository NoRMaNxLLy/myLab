#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int reuse_addr = 1;
char *advice[] = {
        "you have to see the problem, find a solution, and make it a habbit.\r\n",
        "work til you feel tired.\r\n"
};

int main()
{
        unsigned int addr_size;
        int ret;
        int listener_d, connect_d;
        struct sockaddr_in name;
        struct sockaddr_in client_addr;

        name.sin_family = AF_INET;
        name.sin_port = (in_port_t)htons(30000);
        name.sin_addr.s_addr = htonl(INADDR_ANY);

        listener_d = socket(AF_INET, SOCK_STREAM, 0);

        ret = setsockopt(listener_d, SOL_SOCKET, SO_REUSEADDR,
                        &reuse_addr, sizeof(reuse_addr));
        if (ret == -1) {
                perror("setsockopt():");
        }

        ret = bind(listener_d, (struct sockaddr*) &name, sizeof(name));
        if (ret == -1) {
                perror("bind()");
                exit(EXIT_FAILURE);
        }

        ret = listen(listener_d, 10);
        if (ret == -1) {
                perror("listen()");
                exit(EXIT_FAILURE);
        }

        printf("%s\n", "waiting for connections...");

        while (1) {
                addr_size = sizeof(client_addr);
                connect_d = accept(listener_d, (struct sockaddr*) &client_addr,
                                &addr_size);

                send(connect_d, advice[0], strlen(advice[0]), 0);

                close(connect_d);
        }
        return 0;
}
