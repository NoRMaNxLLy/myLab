#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main()
{
	int fd;
	int n;
	char* fifopath = "/tmp/fifo";
	char buf[256];

	fd = open(fifopath, O_RDONLY|O_NONBLOCK);
	if (fd == -1) {
		perror("open()");
		exit(EXIT_FAILURE);
	}
	puts("now opened");

	while ((n = read(fd, buf, sizeof(buf))) > 0) {
                if (write(STDOUT_FILENO, buf, n) != n) {
                        perror("write");
                }
	}
}
