#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b)
{
        while (a != b) {
                if (a > b) {
                        a = a - b;
                } else {
                        b = b - a;
                }
        }

        return a;
}

int main(int argc, char *argv[])
{
        if (argc < 3) {
                fprintf(stderr, "%s n1 n2\n", argv[0]);
                exit(EXIT_FAILURE);
        }

        printf("%d\n", gcd(atoi(argv[1]), atoi(argv[2])));
}
