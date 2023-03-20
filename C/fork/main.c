#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
        printf("the start of fork.c, pid:%d\n", (int) getpid());
        int child = fork();
        if (child == 0) {
                printf("i'm the child. pid: %d\n", (int) getpid());
        }
        printf("i'm the parent of %d, pid:%d\n", child, (int) getpid());
}

