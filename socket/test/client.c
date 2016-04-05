#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

int main (){
	int sockfd;
	struct sockaddr_in dest;
	char buffer[128];
	char resp[10] = "clientack";
	
	//create a socket 
	sockfd = socket (PF_INET, SOCK_STREAM, 0);
	
	//initialize value in dest 
	bzero(&dest, sizeof (dest)); // clean to 0 
	dest.sin_family = PF_INET;
	dest.sin_port = htons(8889);
	dest.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	//connect to server
	connect (sockfd, (struct sockaddr *)&dest, sizeof(dest));

		
	//receive message from sserver and print to screen
	bzero(buffer, 128);
	recv(sockfd, buffer, sizeof(buffer), 0);
	printf ("receive from server %s \n", buffer);
	send(sockfd, resp, sizeof(resp), 0);
	close (sockfd);
	return 0;
}
