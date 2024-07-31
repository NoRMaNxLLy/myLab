#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
        int fd, n, linenum;
        char buf[BUFSIZ];

        if (argc < 3)
                exit(EXIT_FAILURE);

        fd = open(argv[1], O_RDONLY);
        if (fd == -1) {
                fprintf(stdout, "can't open %s: %s", argv[1],
                                strerror(errno));
                exit(EXIT_FAILURE);
        }

        linenum = atoi(argv[2]);
        lseek(fd, linenum, SEEK_END);
        n = read(fd, buf, BUFSIZ);
        write(STDOUT_FILENO, buf, n);
}
