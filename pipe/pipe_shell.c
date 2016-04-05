#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
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
		close (fds[0]);
		
		dup2(fds[1], 1); // duplicate a file descriptor 1 => stdout
		execlp ("ls", "ls", "-l", "./", NULL);
		waitpid(child, NULL, 0);
	}else {
		close (fds[1]);
		
		dup2(fds[0],0); // 0=> stdin
		execvp("more", arg_list);
	}
	//  The  exec()  family  of  functions  replaces  the current process image with a new process image. 
	exit(0);
}
