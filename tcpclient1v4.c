//this is the client side program
//it creates a socket and connects to the server
//when connected it receives input sstream that it outputs on the screen.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>

#define BUFFER 100



int main(int argc, char *argv[])
{
    int sockfd = 0;
    int val = 1;
    int count;
    char inputstring[BUFFER];

    if(argc < 3){
	fprintf(stderr,"Wrong number of arguments\n");
	exit(1);
    }

    printf("%s, %s \n", argv[1], argv[2]);

    //creating the client socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
	fprintf(stderr,"Can not create socket\n");
	exit(2);
    } else {
	printf("socket created\n");
    }



    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(argv[2]));
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);

    //connection with the server
    if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
	fprintf(stderr,"Can not connect to the server, %d, \n", sockfd);
	exit(3);
    }
    getchar();
    //receiving data from the server
    while ((count = read(sockfd, inputstring, BUFFER)) > 0) {
	write(1, inputstring, count);	//outputing the received data on the screen
    }
    close(sockfd);
    return 0;
}
