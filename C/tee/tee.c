#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
        int  out, n;
        int opt_append = 0;
        char buf[BUFSIZ];
        char *filename;
        char opt;

        if (argc < 2)  {
                fprintf(stderr, "usage: %s [-a] FILE\n", argv[0]);
                exit(EXIT_FAILURE);
        }

        while((opt = getopt(argc, argv, "a")) != -1) {
                switch (opt) {
                case 'a':
                        opt_append = 1;
                        break;
                default:
                        fprintf(stderr, "invalid option -- %c\n",
                                        optopt);
                        exit(EXIT_FAILURE);
                }
        }
        argc -= optind;
        argv += optind;

        filename = argv[0];

        if (opt_append) {
                out = open(filename, O_WRONLY|O_CREAT|O_APPEND,
                                S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
        } else {
                out = open(filename, O_WRONLY|O_CREAT|O_TRUNC,
                                S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
        }
        if (out == -1) {
                fprintf(stderr, "can't open %s: %s", filename,
                                strerror(errno));
                exit(EXIT_FAILURE);
        }

        while ((n = read(STDIN_FILENO, buf, BUFSIZ)) > 0) {
                write(STDOUT_FILENO, buf, n);

                if (write(out, buf, n) != n) {
                        fprintf(stderr, "couldn't write buf to %s: %s",
                                        filename, strerror(errno));
                        exit(EXIT_FAILURE);
                }
        }
}
