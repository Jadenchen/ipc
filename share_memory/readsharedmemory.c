#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <stdlib.h>


int main (int argc, char *argv[]){
	int seg_id;
	char *shared_memory;

	/*get shmid*/
	seg_id = atoi(argv[1]);
	
	/*shared memory: attach*/
	shared_memory = (char *) shmat(seg_id, 0, 0);

	/* write to shared memory */
	printf ("message of shared memory : %s\n", shared_memory);

	/* shared memory */ 
	shmdt(shared_memory);
	
	/*deallocate shared memory */
	shmctl(seg_id, IPC_RMID, 0);


	exit(0);

}
