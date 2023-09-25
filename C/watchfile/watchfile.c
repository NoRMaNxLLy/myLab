/* print a file if it has changed */
#include <sys/stat.h>

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

char *progname;

void print(int fd);
void cls();

int main(int argc, char *argv[])
{
        int fd;
        time_t newest_mtime;
        struct stat stbuf;

        progname = argv[0];

        if (argc < 2) {
                fprintf(stderr, "Usage: %s FILE\n", progname);
                exit(EXIT_FAILURE);
        }

        fd = open(argv[1], O_RDONLY);
        if (fd == -1) {
                fprintf(stderr, "%s: can't open %s: %s",
                                progname, argv[1], strerror(errno));
                exit(EXIT_FAILURE);
        }

        /* is this necassary? */
        if (stat(argv[1], &stbuf) == -1) {
                fprintf(stderr, "%s: can't access %s: %s\n",
                                progname, argv[1], strerror(errno));
                exit(EXIT_FAILURE);
        }

        cls();
        print(fd);
        newest_mtime = stbuf.st_mtime;
        for (;;) {
                stat(argv[1], &stbuf);
                if (stbuf.st_mtime > newest_mtime) {
                        cls();
                        print(fd);
                        newest_mtime = stbuf.st_mtime;
                }

                sleep(1);
        }

        close(fd);
        return 0;
}

void print(int fd) {
        int n;
        char buf[BUFSIZ];

        lseek(fd, 0, SEEK_SET);
        while ((n = read(fd, buf, BUFSIZ)) > 0) {
                if (write(STDOUT_FILENO, buf, n) != n) {
                        fprintf(stderr, "%s: write error: %s",
                                        progname, strerror(errno));
                        exit(EXIT_FAILURE);
                }
        }
}

void cls()
{
        // printf("\e[1;1H\e[2J"); /* it is not working -_- */
        system("clear");
}
