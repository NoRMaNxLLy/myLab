/* cp: minimal version */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h> /* for strerror */

#define PERMS 0644
char *progname;

int main(int argc, char *argv[])
{
        int fd1, fd2, n;
        char buf[BUFSIZ];
        progname = argv[0];

        if (argc != 3) {
                fprintf(stderr, "usage: %s SRC DST", progname);
                exit(1);
        }

        if ((fd1 = open(argv[1], 0)) == -1) {
                fprintf(stderr, "can't open '%s': %s\n", argv[1],
                                strerror(errno));
                exit(1);
        }

        if((fd2 = creat(argv[2], PERMS)) == -1) {
                fprintf(stderr, "can't create %s: %s", argv[2],
                                strerror(errno));
                exit(1);
        }

        while((n = read(fd1, buf, sizeof buf)) > 0) {
                if (write(fd2, buf, n) != n) {
                        fprintf(stderr, "%s\n", strerror(errno));
                        exit(1);
                }
        }

        return 0;
}
