/*
filename serrver_ipaddress portno

argv[0] = filename
argv[1] = server_ipaddress
argv[2] = portno
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg)
{
    perror(msg);
    ecit(1);
}

int main(int argc , int argv[])
{
    int sockfd , portno , n;
    struct sockaddr_in serv_addr;
    struct hostent *server; //defines the host ent structure //hostent is used to store info about a given host 

    char buffer[256];
    if(argc<3)
    {
        fpintf(stderr , "usage %s hostname port\n",argv[0]);
        exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET , SOCK_STREAM , 0);
    if(sockfd<0) error("Error opening socket");

    server = gethostbyname(argv[1]);
    if(server == NULL)
    {
        fprintf(stderr , "Error , no such host");
        exit(0);
    }

    bzero((char *) &serv_addr , sizeof(serv_addr));
/*
void bzero(void *s, size_t n);
s: This is a pointer to the starting address of the block of memory that needs to be set to zero.
n: This represents the number of bytes to be set to zero.
*/
}