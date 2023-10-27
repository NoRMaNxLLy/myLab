#include <stdio.h>

#include "checksum.h"
#include "encrypt.h"

int main()
{
        char message[] = "Hello world";
        printf("clear: %s\n", message);
        printf("checksum: %d\n", checksum(message));
        encrypt(message);
        printf("encryptd: %s\n", message);
        printf("checksum: %d\n", checksum(message));

        return 0;
}
