#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#include "encrypt.h"

int main(int argc, char *argv[])
{
        char buf[BUFSIZ];
        int n;

        while ((n = read(STDIN_FILENO, buf, BUFSIZ)) > 0) {
                encrypt(buf);
                if (write(STDOUT_FILENO, buf, n) != n) {
                        perror("write");
                }
        }
}
