#include <stdio.h>

/* how many multiple of 4 or 6 between 1 and 100 are there? */

int main()
{
        int i;
        int counter = 0;

        for (i = 1; i <= 100; i++) {
                if ((i % 4 == 0) || (i % 6 == 0)) {
                        counter++;
                }
        }

        printf("%d number\n", counter);
}
