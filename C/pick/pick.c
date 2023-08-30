#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>

void pick(const char *s);

int main(int argc, char* argv[])
{
        int i;
        //const char* progname = argv[0];
        char buf[BUFSIZ];

        if (argc == 1 || strcmp(argv[1], "-") == 0) {
                while(fgets(buf, sizeof(buf), stdin) != NULL) {
                        buf[strlen(buf) - 1] = '\0';
                        pick(buf);
                }

                exit(0);
        }

        for(i = 1; i < argc; i++) {
                pick(argv[i]);
        }
}

void pick(const char *s)
{
        char c;
        static FILE* tty = NULL;

        if (tty == NULL) {
                tty = fopen("/dev/tty", "a+");
        }

        fprintf(tty, "%s? (y,n,q) ", s);
        c = fgetc(tty);
        switch(c) {
        case 'y':
                fprintf(stdout, "%s\n", s);
                break;
        case 'q':
                exit(0);
        }
}
