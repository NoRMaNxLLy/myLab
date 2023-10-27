#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

int score = 0;
int count_questions = 0;

void end_game(int sig)
{
        printf("Final score: %i out of %i\n", score, count_questions);
        exit(0);
}

int catch_signal(int sig, void (*handler)(int))
{
        struct sigaction action;
        action.sa_handler = handler;
        sigemptyset(&action.sa_mask);
        action.sa_flags = 0;
        return sigaction (sig, &action, NULL);
}

void times_up(int sig)
{
        puts("\nTIME'S UP!");
        raise(SIGINT);
}


void error(char *msg)
{
        fprintf(stderr, "%s: %s\n", msg, strerror(errno));
        exit(EXIT_FAILURE);
}

int main()
{
        int a, b, answer;
        char text[4];

        catch_signal(SIGALRM, times_up);
        catch_signal(SIGINT, end_game);

        srandom(time(NULL));

        while (1) {
                count_questions++;
                a = random() % 11;
                b = random() % 11;

                alarm(5);

                printf("\n%i) What is %i times %i? ", count_questions, a, b);
                fgets(text, 4, stdin);
                answer = atoi(text);

                if (answer == a * b) {
                        score++;
                } else {
                        printf("Wrong! Score: %i out of %i\n", score, count_questions);
                }
        }

        return 0;
}
