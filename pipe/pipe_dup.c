#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (){
	FILE *stream;
	int fds[2];
	int i;
	pid_t child;
	char *arg_list[] = {"more", NULL};


	/* create a pipe */
	pipe(fds);
	
	/* fork a child process */
	child = fork();
	
	if (child != 0){
		close (fds[0]); // close read side
		
		stream = fdopen(fds[1], "w");
		for (i = 0; i < 10; i++){
			fprintf (stream, "hello\n");
			fflush(stream);
		}

		close (fds[1]);
		waitpid (child, NULL, 0); //wait for process to change state
	}else {
		close (fds[1]); // close write side fork will return 0 
		
		dup2(fds[0], 0); //duplicate a file descriptor
		execvp("more", arg_list);   
		//execvp functions provide an array of pointers to null-terminated strings that represent the argument list available
      		//to the new program.
	}

	return 0;

}
