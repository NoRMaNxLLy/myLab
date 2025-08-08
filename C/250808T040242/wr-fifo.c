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
	char* fifopath = "/tmp/fifo";
	char* msg = "hello world";

	fd = open(fifopath, O_WRONLY|O_NONBLOCK);
	if (fd == -1) {
		perror("open()");
		exit(EXIT_FAILURE);
	}
	puts("now opened");

	write(fd, msg, strlen(msg));
}
