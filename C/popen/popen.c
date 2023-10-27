#include <stdio.h>

int main()
{
        char buf[BUFSIZ];
        FILE *pipe = popen("ls -l /", "r");

        while(fgets(buf, BUFSIZ, pipe)) {
                fprintf(stdout, "%s", buf);
        }
}
