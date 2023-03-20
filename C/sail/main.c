#include <stdio.h>
#include <stdlib.h>

struct position
{
        float x;
        float y;
};

void move(char dir, struct position *p);
void show_position(struct position p);

int main()
{
        char direction;
        struct position pos = {0, 0};

        while ((direction = getchar()) != EOF) {
                move(direction, &pos);
                show_position(pos);
        }
}


void move(char dir, struct position *p)
{
        switch(dir) {
        case 'w':
                p->y++;
                break;
        case 's':
                p->y--;
                break;
        case 'd':
                p->x++;
                break;
        case 'a':
                p->x--;
                break;
        }
}

void show_position(struct position p)
{
        printf("(%.3f, %.3f)\n", p.x, p.y);
}
