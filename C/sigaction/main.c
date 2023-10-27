#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sighandle(int num)
{
        printf("stop sending %d -_-\n", num);
}

int main()
{
        struct sigaction act;
        act.sa_handler = &sighandle;

        sigaction(15, &act, NULL);

        printf("you can not kill me ...\n");
        for(;;) {
                sleep(1);
        }
}
