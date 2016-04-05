#include <stdio.h>
#include <unistd.h>


int main (){

	int fds[2];
	
	//create a pipe 
	pipe(fds);
	pid_t child = fork();


	if (child != 0){
		close (fds[0]);
		dup2(fds[1], 1);
		close(fds[1]);
		execlp("wc", "wc", "-l", NULL);
	}else{

		close (fds[1]);
		dup2(fds[0],0);
		close (fds[0]);
		
		execlp("ls", "ls", NULL);
	}

	return 0;
}
