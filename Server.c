/*
TCP server that listens for connections from clients, receives messages, and sends responses.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

/*
stdio.h: Standard input and output functions.
stdlib.h: Standard library functions, including exit() and atoi().
string.h: String manipulation functions, including bzero() and strlen().
unistd.h: UNIX standard functions, including read(), write(), and close().
sys/types.h and sys/socket.h: Socket-related functions and data types.
netinet/in.h: Structures for handling internet addresses.
*/

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc , char *argv[]) //argc -  len of argv
//argv[] contains filename and port number
{
    if(argc < 2)
    {
        fprintf(stderr,"Port number nit provided. Program terminated \n");
        exit(1);
    }

    int sockfd , newsockfd , portno , n;
    char buffer[255]; //to store the message sent 

    struct sockaddr_in serv_addr , cli_addr;
    socklen_t clien ;

    sockfd = socket(AF_INET , SOCK_STREAM , 0);
    if(sockfd<0)
    {
        error("Error opening socket");
    }

    bzero((char *) &serv_addr , sizeof(serv_addr));
    portno = atoi(argv[1]); //converts string to integer

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);  //host to network short

    if(bind(sockfd , (struct sockaddr *) &serv_addr , sizeof(serv_addr)) < 0)
    {
        error("Binding failed");
    }

    listen(sockfd , 5); //5 is the maximum size of the queue of pending connections
    clien = sizeof(cli_addr);

    newsockfd = accept(sockfd , (struct sockaddr *) &cli_addr , &clien);
    
    if(newsockfd<0)
        error("Error on accept");

    while(1)
    {
        bzero(buffer , 255);
        n = read(newsockfd , buffer , 255);
        if(n<0)
        error("Error on reading");
        printf("Client : %s\n",buffer);
        bzero(buffer , 255);

        fgets(buffer , 255 , stdin);

        n = write(newsockfd , buffer , strlen(buffer));
        if(n<0) error("Error on writing");

        int i = strncmp("Bye" , buffer , 3);
        if(i==0) break; 
    }
    close(newsockfd);
    close(sockfd);
    return 0;
}
