#include <stdio.h>
#include <stdlib.h>

typedef struct node {
        int val;
        struct node *next;
} node;

node* new_node(int v)
{
        node* n = (node*)malloc(sizeof(node));
        if (n == NULL) {
                perror("new_node(): ");
                exit(EXIT_FAILURE);
        }
        n->val = v;
        n->next = NULL;

        return n;
}


node* node_add(node *head, int val)
{
        node *i = head;
        node *next;

        if (head == NULL) {
                head = new_node(val);
                return head;
        }

        while (i->next != NULL) {
                i = i->next;
        }

        next = new_node(val);
        i->next = next;

        return head;
}

void nodes_display(node *head)
{
        node *i;
        for (i = head; i != NULL; i = i->next) {
                printf("value = %d\n", i->val);
        }
}

int main()
{
        node *head = NULL;

        head = node_add(head, 10);
        head = node_add(head, 3);
        head = node_add(head, 11);

        nodes_display(head);
}
