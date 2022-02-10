// A simple server in the internet domain using TCP, the port number is passed as an argument */
// required header files for socket programming
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

//method called error, exit(1) means you are exiting from the program
void error(char *msg)
{
  perror(msg);
  exit(1);
}
//argc is command line argument
//argv accepts all arguments
int main(int argc, char *argv[])
{

  int sockfd, newsockfd, portno, clilen;
  char buffer[256]; //send and receive values from serve, using single one
  struct sockaddr_in serv_addr, cli_addr;
  int n;
  // have all encessary command line arguments been given
  if (argc < 2)
  {
    fprintf(stderr, "ERROR, no port provided\n");
    exit(1);
  }

  // the socket section, takes 3 args, 1st arg is im going to use ip, i would like to use tcp, 0 gets me appropriate socket
  // ip/tcp/create socket

  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if (sockfd < 0)
  {
    error("ERROR opening socket");
  }
  //clearing first server addr with bzero method
  bzero((char *) &serv_addr, sizeof(serv_addr));

  //port no passed in command line arg, to convert character to int we use atoi
  portno = atoi(argv[1]);

  //saying to server address, all will be in internet address concept
  serv_addr.sin_family = AF_INET;
  // get your address on your own when you start the program
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  // convert integer format to network format with htons
  serv_addr.sin_port = htons(portno);

  //call bind method and return error message if it doesn't work
  if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
  {
    error("ERROR on binding");
  }
  //going into listen mode, can handle 5 clients
  listen(sockfd, 5);
  clilen = sizeof(cli_addr);

  //creating new socket for particular client that has my address and client address
  //cli_addr provides all the info i need about the client
  newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

  if (newsockfd <0)
  {
    error("ERROR on accept");
  }

  //loop
  //clear the buffer
  bzero(buffer, 256);
  //call read method to buffer, size is 255
  n = read(newsockfd, buffer, 255);

  if (n < 0)
  {
    error("ERROR reading from socket");
  }

  printf("Here is the message: %s\n", buffer);

  //call write method, newsockfd has client information, nchar is 18
  n = write(newsockfd, "I got your message", 18);

  if (n < 0)
  {
    error("ERROR writing to socket");
  }

  return 0;
}
