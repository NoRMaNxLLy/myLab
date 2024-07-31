#include <stdio.h>
#include <stdlib.h>

int value2distance(int v)
{
        // the first 1km costs 3 LYD. the rest costs 1 LYD each
        int km = 1;
        km += v - 3;
        return km;
}

int main()
{
        int value;

        printf("%s", "pay: ");
        scanf("%d", &value);

        if (value <= 4) {
                fprintf(stderr, "pay value must be > 4\n");
                exit(EXIT_FAILURE);
        }

        printf("%dkm\n", value2distance(value));
        return EXIT_SUCCESS;
}
