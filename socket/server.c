#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

#define PORT 2571
#define MAX 1024



char *GetLine(int fd)
{
    char netread[MAX+4], readch;
    ssize_t n;
    int len;

    len = 0;
    while (len < MAX) {
        n = read(fd, &readch,1);
        if (n <= 0)
            break;
        if (strncmp(&readch, "\n", 1) == 0)
            break;

        netread[len++]= readch;
    }

    netread[len] = '\0';
    char *tmp = netread;
    return tmp;
}

int HandleMsgs(char *s)
{
    if (s[0] == '\0')
        return -1;
    else if (strncmp(s, "quit", 4) == 0)
        return -1;
    return 0;
}

int main (int argc, char *argv[])
{
    int sockfd;
    int client_sockfd, len;
    int r;

    char msg[MAX+4];
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    /* create a socket */
    printf ("create a socket\n");
    sockfd = socket (AF_INET, SOCK_STREAM, 0); //AF_INET means address family
    if (sockfd == -1) {
        printf ("failed to create a socket\n");
        perror (NULL);
        exit(1);
    }

    /*bind an address to the socket*/
    printf ("bind a address to a socket\n");
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // convert values between host and network byte order
    server_addr.sin_port = htons(PORT); //convert values between host and network byte order

    if (bind(sockfd,(struct sockaddr *) &server_addr, sizeof(struct sockaddr_in))< 0) {
        printf ("failed to bind a socket\n");
        perror(NULL);
        exit(1);
    }


    /* listen for connections */
    printf ("listening for connection...\n");
    listen(sockfd, 5);

    /* accept a connection */
    printf ("accept a connection \n");
    len = sizeof (struct sockaddr_in);
    client_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &len);

    if (client_sockfd == -1) {
        printf ("failed to accep a connection\n");
        perror(NULL);
        exit(1);
    }

    printf ("Connection Accepted \n\n");

    /* receive and handling message */
    printf ("receive and handling messages\n");
    r = 0;
    while (1) {
        strcpy(msg, GetLine(client_sockfd));
        r = HandleMsgs(msg);
        if (r == -1)
            break;
        printf ("Receive: %s \n", msg);
    }

    close (client_sockfd);
    exit(0);
}
