/* vis command from unix programming environment.
   outputs non-printable character as \0nnn */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int strip = 0;

void vis(FILE* fp)
{
        int c;
        while ((c = getc(fp)) != EOF) {
                if (isascii(c) && (isprint(c) || c == '\n' || c == '\t' || c == ' '))
                        putchar(c);
                else if (!strip)
                        printf("\\%03o", c);
        }
}

int main(int argc, char *argv[])
{
        opterr = 0;
        int opt;
        const char* prog = argv[0];

        while ((opt = getopt(argc, argv, "s")) != -1) {
                switch(opt) {
                case 's':
                        strip = 1;
                        break;
                default:
                        fprintf(stderr, "%s: invalid option -- %c\n",
                                        argv[0], optopt);
                        exit(1);
                }
        }

        argc -= optind;
        argv += optind;

        if (argc == 0) {
                vis(stdin);
                return 0;
        }

        int i;
        FILE* fp;
        for (i = 0; i < argc; i++) {
                fp = fopen(argv[i], "r");
                if (fp == NULL) {
                        fprintf(stderr, "%s: can't open %s\n",
                                        prog, argv[i]);
                        return 1;
                }

                vis(fp);
                fclose(fp);
        }
}
