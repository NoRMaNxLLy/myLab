/* output printable argument filenames */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>

int printable(const char* s)
{
        int i;
        int len = strlen(s);

        for (i = 0; i < len; i++) {
                if (!isgraph(s[i])) return 0;
        }

        return 1;
}

int main(int argc, char* argv[])
{
        opterr = 0;
        int opt;
        const char* prog = argv[0];
        int invmatch = 0;

        while ((opt = getopt(argc, argv, "v")) != -1) {
                switch(opt) {
                case 'v':
                        invmatch = 1;
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
                fprintf(stderr, "usage: %s [-v] FILENAME...\n", prog);
                exit(EXIT_FAILURE);
        }

        int i;
        if (invmatch) {
                for (i = 0; i < argc; i++) {
                        if (!printable(argv[i])) puts(argv[i]);
                }
                return 0;
        }

        for (i = 0; i < argc; i++) {
                if (printable(argv[i])) puts(argv[i]);
        }

        return 0;
}
