#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

void pipe_write (const char *msg, FILE *stream){
	int i;

	for (i = 0; i< 1;i++){
		fprintf(stream, "%s\n", msg);

		fflush(stream); // 
		sleep(3);
	}
}

void pipe_read(FILE *stream){
	char buffer[1024];
	
	while (!feof(stream) && !ferror(stream) && fgets(buffer, sizeof(buffer), stream) != NULL)
		fputs(buffer, stdout);
}


int main (){

	int fds[2]; // fds[0] for write  fds[1] for read
	FILE *stream;
	pid_t self, child;

	/* create a pipe*/
	pipe(fds);
	
	/* fork s child process */
	self = getpid();
	child = fork();
	
	printf ("main function \n");

	if (child != 0){
		printf ("parent process PID id %d\n ", (int) self);
		printf ("child process id %d\n", (int) child);
		close(fds[0]);
		
		/* write pipe from the parent process */
		stream = fdopen(fds[1], "w"); //fds[1] is for write
		pipe_write("hello pipes", stream);
		close (fds[1]);
	}else{
		printf ("this is the child process PID %d\n", (int)getpid());
		close (fds[1]);
	
		/* read pipe from the child process */
		stream =fdopen(fds[0], "r"); // fds[0] is for read
		pipe_read(stream);
		close (fds[0]);
	}
	return 0;

}

