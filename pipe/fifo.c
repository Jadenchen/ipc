#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main (){
	int fd = ("/tmp/fifo", O_WRONLY);
	write(fd, "hello", 5);
	close (fd);
	return 0;
}
