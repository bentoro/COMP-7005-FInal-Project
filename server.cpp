#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <errno.h>

#define BUFLEN			80  	// Buffer length
#define SVR_PRT 7005
int main (int argc, char *argv[]) {
  struct hostent	*hp;
  struct sockaddr_in server, client, server1;
  int port, cmdsocket, sd, datasocket;
  socklen_t client_len;
  //char *host;
  char *bf, buf[BUFLEN];
  int n, read;

  /*if(argc != 0){
    printf("Error : [port]");
    exit(1);
  } else {
    port = atoi(argv[0]);
  }*/
  if ((cmdsocket = socket(AF_INET, SOCK_STREAM,0)) == -1){
    printf("Error creating socket");
    exit(1);
  }else {
    printf("Socket created \n");
  }
  bzero((char *)&server, sizeof(struct sockaddr_in));
  server.sin_family = AF_INET;
  server.sin_port = htons(7005);
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  if ((bind(cmdsocket,(struct sockaddr *)&server,sizeof(server))) == -1){
    printf("Error binding socket");
    exit(1);
  } else {
    printf("Binding socket\n");
  }

  listen(cmdsocket,5);
  client_len = sizeof(client);
  if ((sd = accept(cmdsocket,(struct sockaddr *) &client, &client_len)) == -1){
    printf("Error accepting client");
    exit(1);
  } else {
    printf("Client connected\n");
  }


  //********************************************************
  //data socket
  //create command socket, returns socket file descriptor(int)
  if ((datasocket = socket(AF_INET, SOCK_STREAM,0)) == -1){
    printf("Error creating socket\n");
    exit(1);
  } else {
    printf("Socket created\n");
  }
  //empties the pointer to the buffer and the size of the buffer is cleared
  bzero((char *)&server1, sizeof(struct sockaddr_in));
  server1.sin_family = AF_INET;
  server1.sin_port = htons(7006);
  hp = gethostbyname("127.0.0.1");
  //copies the host address into the hostent struct
  bcopy(hp->h_addr, (char *)&server1.sin_addr, hp->h_length);
  //connect takes socket file descriptor, address of host including port, and the size of the address
  if ((connect(datasocket,(struct sockaddr *)&server1, sizeof(server1))) == -1){
    printf("Error connectiong to server\n");
    exit(1);
  } else {
    printf("Connected to server\n");
  }
  //data socket
  //********************************************************


  bf = buf;
  read = BUFLEN;
  while ((n = recv(sd, bf, sizeof(buf), 0)) < 0){
  }
  printf ("client:%s\n", buf);

  /*printf("Please enter a message to send to the server: ");
  bzero(buf,sizeof(buf));
  fgets(buf, BUFLEN, stdin);
  send(sd, buf, BUFLEN, 0);*/

}
