#include "checksum.h"

int checksum(char *message)
{
        int c = 0;

        for (; *message != '\0'; message++) {
                c += c ^ (int)(*message);
        }

        return c;
}
