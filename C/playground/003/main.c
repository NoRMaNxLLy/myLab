#include <stdio.h>
#include <stdlib.h>

int cube(int n)
{
        return n * n * n;
}

// even or odd
int even(int n)
{
        return n % 2 == 0? 1: 0;
}

int main()
{
        int n, next, sum = 0;

        printf("n: ");
        scanf("%d", &n);

        next = n + 1;
        if (!even(next))
                next++;

        printf("%d\n", next);

        for (int i = next; i >= 1; i--)
                sum += cube(i);

        printf("%d\n", sum);

        return EXIT_FAILURE;
}
