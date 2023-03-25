#include <stdio.h>

#define BUFSIZE 256

/* true if c between a and m*/
int aTOm(char c) { return 97 <= c && c <= 109? 1: 0; }

/* true if c between n and z*/
int nTOz(char c) { return 110 <= c && c <= 122? 1: 0; }

/* true if c between A and M*/
int AtoM(char c) { return 65 <= c && c <= 77? 1: 0; }

/* true if c between N and Z*/
int NtoZ(char c) { return 78 <= c && c <= 90? 1: 0; }

void rot13(char *str)
{
        char *c;
        for (c = str; *c != '\0'; c++) {
                if (aTOm(*c) || AtoM(*c)) {
                        *c += 13;
                } else if (nTOz(*c) || NtoZ(*c)) {
                        *c -= 13;
                }
        }
}

int main()
{
        char buf[BUFSIZE];
        while (fgets(buf, BUFSIZE, stdin)) {
                rot13(buf);
                printf("%s", buf);
        }
}
