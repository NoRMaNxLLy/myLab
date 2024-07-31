#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[])
{
        int i = 0, protonum;
        struct protoent *ent;

        if (argc < 2) {
                while ((ent = getprotoent())) {
                        printf("%-20s %d", ent->p_name, ent->p_proto);
                        for (i = 0; ent->p_aliases[i] != NULL; i++) {
                                printf(" %s", ent->p_aliases[i]);
                        }
                        printf("\n");
                }
                exit(EXIT_SUCCESS);
        }

        ent = getprotobyname(argv[1]);
        if (ent == NULL) {
                char *ptr = NULL;
                protonum = strtol(argv[1], &ptr, 10);
                if (*ptr != '\0')
                        exit(EXIT_FAILURE);

                ent = getprotobynumber(protonum);
                if (ent == NULL)
                        exit(EXIT_FAILURE);
        }

        printf("%-20s %d", ent->p_name, ent->p_proto);
        for (i = 0; ent->p_aliases[i] != NULL; i++) {
                printf(" %s", ent->p_aliases[i]);
        }
        printf("\n");
}
