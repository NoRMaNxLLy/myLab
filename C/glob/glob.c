/* expand glob pattern arguments*/
#include <stdio.h>
#include <stdlib.h>
#include <glob.h>

int main(int argc, char *argv[])
{
        char **path;
        glob_t res;

        if (argc < 2) {
                fprintf(stderr, "%s globpattern\n", argv[0]);
                exit(EXIT_FAILURE);
        }

        int i, ret;
        for (i = 0; i < argc; i++) {
                ret = glob(argv[i], 0, NULL, &res);
                switch (ret) {
                case GLOB_NOSPACE:
                        fprintf(stderr, "no memory\n");
                        globfree(&res);
                        break;
                case GLOB_ABORTED:
                        fprintf(stderr, "read error\n");
                        globfree(&res);
                        break;

                }

                for (path = res.gl_pathv; *path != NULL; path++) {
                        printf("%s\n", *path);
                }
        }

        globfree(&res);
}
