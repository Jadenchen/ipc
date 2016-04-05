#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <unistd.h>

#define FILE_LENGTH 0x400

int main (int argc, char *argv[]){
	int fd;
	void *map_memory;
	/*open a file to be mapped */

	fd = open("/tmp/shared_file", O_RDWR | O_CREAT, S_IRUSR| S_IWUSR);
	lseek(fd, FILE_LENGTH+1, SEEK_SET);
	write(fd, "",1);
	lseek(fd, 0,SEEK_SET);

	/*create map memory */
	map_memory = mmap(0, FILE_LENGTH, PROT_WRITE, MAP_SHARED, fd, 0);
	close(fd);

	/* write to mmaped memory */
	if (strlen(argv[1])< FILE_LENGTH)
		sprintf((char *)map_memory, "%s", argv[1]);

	exit(0);

}
