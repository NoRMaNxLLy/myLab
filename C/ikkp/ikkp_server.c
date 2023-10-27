#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int lsock;
int lport = 30000;

void error(char *msg)
{
        perror(msg);
        exit(1);
}

void handle_shutdown(int sig)
{
        if (lsock)
                close(lsock);
        fprintf(stderr, "Bye!\n");
        exit(sig);
}

int open_listener_socket()
{
        int s = socket(AF_INET, SOCK_STREAM, 0);
        if (s == -1)
                error("socket()");
        return s;
}

void bind_to_port(int socket, int port)
{
        int c, reuseaddr = 1;
        struct sockaddr_in name;

        name.sin_family = AF_INET;
        name.sin_port = (in_port_t)htons(port);
        name.sin_addr.s_addr = htonl(INADDR_ANY);

        if (setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (char *)&reuseaddr, sizeof(int)) == -1)
                error("setsockopt");

        c = bind (socket, (struct sockaddr *) &name, sizeof(name));
        if (c == -1)
                error("bind()");
}

int say(int socket, char *s)
{
        int result = send(socket, s, strlen(s), 0);

        if (result == -1)
                fprintf(stderr, "%s: %s\n", "Error talking to the client", strerror(errno));

        return result;
}

int read_in(int socket, char *buf, int len)
{
        char *s = buf;
        int slen = len;
        int c = recv(socket, s, slen, 0);

        while ((c > 0) && (s[c-1] != '\n')) {
                s += c; slen -= c;
                c = recv(socket, s, slen, 0);
        }
        if (c < 0) 
                return c;
        else if (c == 0)
                buf[0] = '\0';
        else
                s[c-1]='\0';
        return len - slen;
}

void start_knocking(int socket)
{
        char buf[256];

        say(socket, "Knock! Knock!\r\n");
        read_in(socket, buf, 256);
        if (strcasecmp(buf, "who's there?") != 0) {
                say(socket, "you should say 'who's there'!!\r\n");
                return;
        }

        say(socket, "Oscar!\r\n");
        read_in(socket, buf, 256);
        if (strcasecmp(buf, "oscar who?") != 0) {
                say(socket, "you should say 'oscar who'!!\r\n");
                return;
        }

        say(socket, "oscar silly question, you get a silly answer.\r\n");
}

int main()
{
        int err, csock, pid; /* connection */
        socklen_t caddr_len;
        struct sockaddr_storage caddr;

        lsock = open_listener_socket();
        if (lsock == -1) {
                error("socket()");
        }

        bind_to_port(lsock, lport);

        err = listen(lsock, 10);
        if (err == -1) {
                error("listen()");
        }

        printf("%s\n", "waiting for connections...\n");

        for (;;) {
                csock = accept(lsock, (struct sockaddr*) &caddr, &caddr_len);
                if (csock == -1) {
                        error("accept()");
                }

                pid = fork();
                if (pid == -1) {
                        error("fork()");
                }

                if (pid == 0) {
                        close(lsock);
                        start_knocking(csock);
                        close(csock);
                        exit(0);
                }

                close(csock);
        }
}
