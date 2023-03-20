#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rm_nl(char *s)
{
        size_t len = strlen(s);
        s[len - 1] = '\0';
}

void backwords(char *s)
{
        size_t len = strlen(s);
        for(int i = len - 1; i >= 0; i--) {
                printf("%c", s[i]);
        }
}

int main()
{
        char s[256];
        printf("enter string to display it backword: ");
        fgets(s, 256, stdin);
        rm_nl(s);
        backwords(s);
        return 0;
}
