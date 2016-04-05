#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include<stdlib.h>
#include <stdio.h>
#include <unistd.h>


int main (){
	int sockfd;
	struct sockaddr_in dest;
	char buffer[20] = "hi client";
	char buffer1[10];
	
	//create socket 
	sockfd = socket (PF_INET, SOCK_STREAM, 0);
	
	//intitialize struct dest
	bzero(&dest, sizeof (dest));
	dest.sin_family = AF_INET;
	dest.sin_port = htons(8889);
	//this line is different from client
	dest.sin_addr.s_addr = INADDR_ANY;
	
	//assigned a port 
	bind(sockfd, (struct sockaddr *)&dest, sizeof(dest));
	
	//make it listen to socket with max 20 connections
	listen(sockfd, 20);

	//accept connection from client

	while (1){
		int clientfd;
		struct sockaddr_in client_addr;
		int addrlen = sizeof(client_addr);
	
		// wait and accept connection 
		clientfd = accept(sockfd, (struct sockaddr *)&client_addr, &addrlen);
		
		//send message 
		send (clientfd, buffer, sizeof(buffer),0);
		int res = recv(clientfd, buffer1, sizeof(buffer1),0);
		printf ("receive from client %s , %d bytes\n", buffer, res);

		//close client
		close (sockfd);
	}

}
