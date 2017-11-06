#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFLEN			80  	// Buffer length
#define SVR_PRT 7005
int main (int argc, char *argv[]) {
  struct sockaddr_in server, client;
  int port, cmdsocket, sd;
  socklen_t client_len;
  char *host;
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
  }
  printf("CONNECTIONG TO CLIENT");
  bzero((char *)&server, sizeof(struct sockaddr_in));
  server.sin_family = AF_INET;
  server.sin_port = htons(7005);
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  if ((bind(cmdsocket,(struct sockaddr *)&server,sizeof(server))) == -1){
    printf("Error binding socket");
    exit(1);
  } else {
    printf("Binding socket");
  }

  listen(cmdsocket,5);
  client_len = sizeof(client);
  if ((sd = accept(cmdsocket,(struct sockaddr *) &client, &client_len)) == -1){
    printf("Error accepting client");
    exit(1);
  } else {
    printf("Client connected");
  }

  bf = buf;
  read = BUFLEN;
  while ((n = recv(sd, bf, sizeof(buf), 0)) < 0){

  }
  printf ("sending:%s\n", buf);
  printf("Please enter a message to send to the server: ");
  bzero(buf,sizeof(buf));
  fgets(buf, BUFLEN, stdin);
  send(sd, buf, BUFLEN, 0);

}
