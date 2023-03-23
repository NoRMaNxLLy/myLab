#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 256

void cat(const char *fname)
{
        char buf[BUFSIZE];
        FILE *f = fopen(fname, "r");
        while (fgets(buf, BUFSIZE, f)) {
                printf("%s", buf);
        }
        fclose(f);
}

int main(int argc, char **argv)
{
        int i;
        if (argc < 2) {
                exit(EXIT_FAILURE);
        }

        for (i = 1; i < argc; i++) {
                cat(argv[i]);
        }
}
