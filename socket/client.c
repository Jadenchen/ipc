#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 2571
#define MAX 1024



void HandleMsgs (int fd)
{
    char buf[MAX+4];

    while (1) {
        scanf("%s", buf);
        if (strlen (buf) > MAX)
            buf[MAX-1] = '\0';

        if (strncmp(buf, "quit", 4) == 0) {
            return ;
        } else {
            write (fd, buf, strlen(buf));
            write (fd, "\n", 1);
            printf ("Sent: %s\n", buf);
        }

    }
}

int main (int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_in serv_addr;

    if (argc != 2) {
        printf ( "USAGE %s server IP\n", argv[0]);
        exit(1);
    }

    /* create a socket */
    printf ("create a socket \n");
    sockfd = socket (PF_INET, SOCK_STREAM, 0); //PF_INET protocol family
    if (sockfd == -1) {
        printf ("failed to create a socket\n");
        perror ("create socket failed ");
        exit(1);
    }

    /* connect to a server */
    printf ("connect to a server\n");
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr= inet_addr(argv[1]);
    serv_addr.sin_port = htons(PORT);

    if (connect(sockfd,(struct sockaddr *) &serv_addr, sizeof(struct sockaddr_in))< 0) {
        printf ("failed to connect to server\n");
        perror (NULL);
        exit(1);
    }

    printf ("type quit to exit \n\n");
    HandleMsgs(sockfd);
    close(sockfd);
    exit(0);
}
