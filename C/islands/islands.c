#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct island {
        char *name;
        char *opens;
        char *closes;
        struct island *next;
} island;

void display(island *start);
island* create(char *name);
void release(island *start);

int main()
{
        island *start = NULL;
        island *next = NULL;
        island *i = NULL;
        char landname[80];

        while (fgets(landname, 80, stdin) != NULL) {
                landname[strlen(landname) - 1] = '\0';
                next = create(landname);

                if (start == NULL) {
                        start = next;
                }

                if (i != NULL) {
                        i->next = next;
                }

                i = next;
        }

        display(start);
        release(start);
}

void display(island *start)
{
        island *i = start;

        for (; i != NULL; i = i->next) {
                printf("Name: %s\nopen: %s-%s\n\n", i->name, i->opens,
                                i->closes);
        }
}

island* create(char *name)
{
        island *i = malloc(sizeof(island));

        i->name   = strdup(name);
        i->opens  = "09:00";
        i->closes = "17:00";
        i->next   = NULL;

        return i;
}

void release(island *start)
{
        island *i = start;
        island *next = NULL;

        for (; i != NULL; i = next) {
                next = i->next;
                free(i->name);
                free(i);
        }
}
