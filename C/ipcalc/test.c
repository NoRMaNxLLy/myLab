#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int validmask(unsigned int mask) {
        unsigned int i = 0x80000000;
        int found_zero = 0;

        while (i) {
                printf("%08x\n", mask & i);
                if ((mask & i) == 0)
                        found_zero = 1;

                /* if the bit is set and we already found one off, then
                 * not valid mask */
                if (mask & i && found_zero)
                        return 0;

                i >>= 1;
        }

        return 1;
}

int main(int argc, char *argv[])
{
        (void)argc;
        unsigned int mask = htonl(strtol(argv[1], NULL, 10));

        if (!validmask(mask)) {
                printf("not a valid mask\n");
        }

        if (validmask(mask)) {
                printf("valid mask\n");
        }
}
