#include <stdio.h>
#include <stdlib.h>

int fact(int n)
{
        /* get factorial */
        if (n <= 1) {
                return 1;
        }

        return n * fact(n - 1);
}

int C(int n, int r)
{
        /* find combination */
        return fact(n) / (fact(r) * fact(n - r));
}

void print_pascal_row(int r)
{
        /* print the elements of each row. ex: if r = 4 then find the
         * combinations 4C0, 4C1, 4C2, 4C3, 4C4
         */

        int i;

        for (i = 0; i <= r; i++) {
                printf("%d\t", C(r, i));
        }
        printf("\n");
}

void pascal_triangle(int n)
{
        int i;

        for (i = 0; i <= n; i++) {
                print_pascal_row(i);
        }
}

int main(int argc, char *argv[])
{
        if (argc < 2) {
                printf("%s <N_of_Rows>\n", argv[0]);
                exit(EXIT_FAILURE);
        }

        pascal_triangle(atoi(argv[1]));
}
