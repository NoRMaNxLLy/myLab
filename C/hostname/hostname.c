#include <stdio.h>
#include <unistd.h>

int main()
{
        char buf[64];
        gethostname(buf, sizeof buf);
        printf("%s\n", buf);
}
