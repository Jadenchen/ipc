#include <unistd.h>

int main (){
	
	//execlp ("ps", "ps", NULL);
	char *arg_list[] = {"more", NULL};
	execvp("more", arg_list);

	return 0;
}
