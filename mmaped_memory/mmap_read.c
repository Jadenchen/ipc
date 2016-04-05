#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <unistd.h>
#define FILE_LENGTH 0x400

int main (){

	int fd;
 	void *map_memory;
	char buf[FILE_LENGTH];

	/*open mapped file */

	fd = open ("/tmp/shared_file", O_RDWR, S_IRUSR|S_IWUSR);
	
	/*create mapped memory */
	map_memory = mmap(0, FILE_LENGTH, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	close (fd);

	/* read from mapped memory */
	sscanf ((char *)map_memory, "%s", buf);
	printf ("read: %s\n", buf);

	exit(0);

}
