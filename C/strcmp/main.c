#include <stdio.h>
#include <string.h>

// xD

int main() {
    char  mypass[64] = "hello world\n";
    char  pass[512];
    printf("password: ");
    fgets(pass, 512, stdin);

    if (strcmp(pass, mypass) == 0) {
        printf("get in!!!\n");
        return 0;
    }

    printf("wrong password.\n");
    return 1;
}
