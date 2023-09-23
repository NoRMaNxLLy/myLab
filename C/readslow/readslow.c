/* readslow: keep reading, waiting for more */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

unsigned int sec = 1;

int main(int argc, char *argv[])
{
        char buf[BUFSIZ];
        int n;

        if (argc == 3 && strcmp(argv[1], "-n") == 0)
                sec = atoi(argv[2]);

        for(;;) {
                while((n = read(0, buf, BUFSIZ)) > 0)
                        write(1, buf, n);
                sleep(sec);
        }
}
