#include <stdio.h>
#include <stdlib.h>

int rev(int n)
{
        int r = 0;
        while (n > 0) {
                r *= 10;
                r += n % 10;
                n /= 10;
        }

        return r;
}

int main()
{
        printf("%d\n", rev(123456789));
        return EXIT_SUCCESS;
}
