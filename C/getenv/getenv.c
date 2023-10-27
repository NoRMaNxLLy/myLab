#include <stdio.h>
#include <stdlib.h>

int main()
{
        fprintf(stdout, "%s\n", getenv("USER"));
}
