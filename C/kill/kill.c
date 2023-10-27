#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>

char *progname;

int main(int argc, char *argv[])
{
        int i, signum = SIGTERM;
        pid_t pid;
        progname = argv[0];

        if (argc < 2) {
                fprintf(stderr, "%s: [-SIGNUM] PID\n", argv[0]);
                exit(EXIT_FAILURE);
        }
        argc--, argv++;

        if (argv[0][0] == '-') {
                argv[0]++;
                signum = atoi(argv[0]);
        argc--, argv++;
        }

        for (i = 0; i < argc; i++) {
                pid = atoi(argv[i]);
                if (kill(pid, signum) == -1) {
                        fprintf(stderr, "cant kill %d: %s\n", pid,
                                        strerror(errno));
                }
        }
}
