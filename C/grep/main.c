#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 256

void lookfor(FILE *stream, const char *s)
{
        char line[BUFSIZE];
        while (fgets(line, BUFSIZE, stream)) {
                if (strstr(line, s)) {
                        printf("%s", line);
                }
        }
}

int main(int argc, char* argv[])
{
        if (argc < 2) {
                exit(EXIT_FAILURE);
        }

        if (argv[2] != NULL) {
                FILE* file = fopen(argv[2], "r");
                if (file == NULL) {
                        printf("could not open %s\n", argv[2]);
                        return 1;
                }
                lookfor(file, argv[1]);
                fclose(file);
                exit(EXIT_SUCCESS);
        }

        lookfor(stdin, argv[1]);
        return 0;
}
