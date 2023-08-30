/* a screen at a time printer */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>

int pagesize = 22;
char* progname;

void print(FILE* fp);
void ttyin();
FILE* efopen(const char* file, const char* mode);

int main(int argc, char* argv[])
{
        int i = 0;
        FILE* fp;
        progname = argv[0];

        if (argc == 1) {
                print(stdin);
                return 0;
        }

        for (i = 1; i < argc; i++) {
                fp = efopen(argv[i], "r");
                print(fp);
                fclose(fp);
        }
}

void print(FILE* fp)
{
        char buf[BUFSIZ];
        int lines = 0;

        while (fgets(buf, sizeof(buf), fp)) {
                if (++lines < pagesize) {
                        fputs(buf, stdout);
                } else {
                        buf[strlen(buf) - 1] = '\0';
                        fputs(buf, stdout);
                        fflush(stdout);
                        ttyin();
                        lines = 0;
                }
        }
}

FILE* efopen(const char* file, const char* mode)
{
        FILE* fp;

        if ((fp = fopen(file, mode)) == NULL) {
                fprintf(stderr, "%s: can't open %s mode %s\n", progname, file, mode);
                exit(1);
        }

        return fp;
}
/* read response from tty */
void ttyin()
{
        char buf[BUFSIZ];
        static FILE* tty = NULL;

        if (tty == NULL) {
                tty = fopen("/dev/tty", "r");
        }

        if (fgets(buf, sizeof(buf), tty) == NULL || buf[0] == 'q') {
                exit(0);
        }
}
