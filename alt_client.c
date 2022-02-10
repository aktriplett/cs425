// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

//method called error, exit(0) means you are exiting from the program
void error(char *msg)
{
  perror(msg);
  exit(0);
}

//argc is command line argument
//argv accepts all arguments
int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];

    if (argc < 3)
    {
      fprintf(stderr, "usage %s hostname port\n", argv[0]);
      exit(0);
    }

    portno = atoi(argv[2]);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
    {
      error("ERROR opening socket");
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;

    fprintf(stderr,"before ip get");
    //bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,server->h_length);
    inet_aton(argv[1], &serv_addr.sin_addr.s_addr);
    fprintf(stderr,"after ip get");

    serv_addr.sin_port = htons(portno);

    if (connect(sockfd, &serv_addr, sizeof(serv_addr)) < 0)
    {
      error("ERROR connecting");
    }

    //loop here

    //printf("Enter length of message as int: ");
    //len = int(stdin)
    //bzero(buffer, len)
    printf("Please enter the message: ");
    //bzero(buffer, length(stdin));
    fgets(buffer, length(stdin)-1, stdin);
    //fgets(buffer, len, stdin)
    n = write(sockfd, buffer, strlen(buffer));

    if (n < 0)
    {
      error("ERROR writing to socket");
    }

    bzero(buffer, 256);
    n = read(sockfd, buffer, 255);

    if (n < 0)
    {
      error("ERROR reading from socket");
    }

    printf("%s\n", buffer);

    return(0);
}
