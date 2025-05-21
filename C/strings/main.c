#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int MINLEN = 4;
char* progname;

void strings(char *name, FILE *fin);

// void strings(FILE *f)
// {
// 	int i, c;
// 	char buf[BUFSIZ];
// 
// 	while(1) {
// 		for(i = 0; (c = fgetc(f));) {
// 			if (!isprint(c)) {
// 				break;
// 			}
// 			buf[i++] = c;
// 			if (i >= BUFSIZ) {
// 				break;
// 			}
// 
// 		}
// 		if (i >= MINLEN) {
// 			printf("%s\n", buf);
// 		}
// 		if (c == EOF) {
// 			break;
// 		}
// 	}
// }

int main(int argc, char *argv[])
{
	int i;
	FILE* f;

	progname = argv[0];
	if (argc < 2) {
		fprintf(stderr, "%s: %s\n", progname, "FILE...");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < argc; i++) {
		f = fopen(argv[i], "r");
		if (f == NULL) {
			fprintf(stderr, "can't open file: %s\n", argv[i]);
			exit(EXIT_FAILURE);
		}
		strings(argv[i], f);
		fclose(f);
	}
}

void strings(char *name, FILE *fin)
{
	int c, i;
	char buf [BUFSIZ];
	do {
		   for (i=0;(c = getc(fin)) != EOF;) {
		   if (!isprint(c))
			   break;
		   buf[i++] = c;
		   if (i >= BUFSIZ)
			   break;
		   }
		   if (i >= MINLEN)
			   printf("%s:%.*s\n", name, i , buf);
	} while (c != EOF);
}
