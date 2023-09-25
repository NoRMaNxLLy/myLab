/* sv: copy new files to a directory */
#include <sys/stat.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

char *progname;

int sv(const char *file, const char *dir);
int cp(const char *in, const char *out);

int main(int argc, char *argv[])
{
        struct stat stbuf;
        char *dir = argv[argc - 1];

        progname = argv[0];
        if (argc <= 2) {
                fprintf(stderr, "Usage: %s FILES... DIR\n", progname);
                exit(EXIT_FAILURE);
        }

        if (stat(dir, &stbuf) == -1) {
                fprintf(stderr, "%s: can't stat directory %s: %s",
                                progname, dir, strerror(errno));
                exit(EXIT_FAILURE);
        }

        if ((stbuf.st_mode & S_IFMT) != S_IFDIR) {
                fprintf(stderr, "%s is not a directory", dir);
                exit(EXIT_FAILURE);
        }

        int i;
        for (i = 1; i < argc - 1; i++) {
                sv(argv[i], dir);
        }
}

int sv(const char *file, const char *dir) 
{
        struct stat stat_in, stat_out;
        char target[BUFSIZ];

        if (stat(file, &stat_in) == -1) {
                fprintf(stderr, "%s: can't stat %s: %s", progname, file,
                                strerror(errno));
                exit(EXIT_FAILURE);
        }

        snprintf(target, BUFSIZ, "%s/%s", dir, file);

        /* if the target is not present */
        if (stat(target, &stat_out) == -1) {
                stat_out.st_mtime = 0;
        }

        if (stat_in.st_mtime < stat_out.st_mtime) {
                fprintf(stderr, "%s is not copied: %s is newer", file,
                                target);
                return 0; /* or should we exit? */
        }

        cp(file, target);
        return 1;
}

int cp(const char *in, const char *out)
{
        int fd1, fd2, n;
        char buf[BUFSIZ];

        fd1 = open(in, O_RDONLY);
        if (fd1 == -1) {
                fprintf(stderr, "can't open '%s': %s\n", in,
                                strerror(errno));
                exit(EXIT_FAILURE);
        }

        fd2 = open(out, O_WRONLY|O_CREAT|O_TRUNC,
                        S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
        if(fd2 == -1) {
                fprintf(stderr, "can't create %s: %s", out,
                                strerror(errno));
                exit(EXIT_FAILURE);
        }

        while((n = read(fd1, buf, BUFSIZ)) > 0) {
                if (write(fd2, buf, n) != n) {
                        fprintf(stderr, "%s\n", strerror(errno));
                        exit(EXIT_FAILURE);
                }
        }

        return 1;
}
