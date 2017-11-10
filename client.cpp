#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string>

using namespace std;

#define BUFLEN			1024  	// Buffer length



int main (int argc, char *argv[]) {
  struct hostent	*hp;
  struct sockaddr_in server, server1, client;
  char *bf, buf[BUFLEN];
  int port, cmdsocket, datasocket;
  socklen_t client_len;
  //char *host;
  string msg;
  int n, rd, da;

    //create command socket, returns socket file descriptor(int)
    if ((cmdsocket = socket(AF_INET, SOCK_STREAM,0)) == -1){
      printf("Error creating socket\n");
      exit(1);
    } else {
      printf("Socket created\n");
    }
    //empties the pointer to the buffer and the size of the buffer is cleared
    bzero((char *)&server, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(7005);
    hp = gethostbyname("127.0.0.1");
    //copies the host address into the hostent struct
    bcopy(hp->h_addr, (char *)&server.sin_addr, hp->h_length);
    //connect takes socket file descriptor, address of host including port, and the size of the address
    if ((connect(cmdsocket,(struct sockaddr *)&server, sizeof(server))) == -1){
      printf("Error connectiong to server\n");
      exit(1);
    } else {
      printf("Connected to server\n");
    }

    //*******************************************************
    //datasocket
    if ((datasocket = socket(AF_INET, SOCK_STREAM,0)) == -1){
      printf("Error creating socket");
      exit(1);
    }else {
      printf("Socket created \n");
    }
    bzero((char *)&server1, sizeof(struct sockaddr_in));
    server1.sin_family = AF_INET;
    server1.sin_port = htons(7006);
    server1.sin_addr.s_addr = htonl(INADDR_ANY);
    if ((bind(datasocket,(struct sockaddr *)&server1,sizeof(server1))) == -1){
      printf("Error binding socket");
      exit(1);
    } else {
      printf("Binding socket\n");
    }

    listen(datasocket,5);
    client_len = sizeof(client);
    if ((da = accept(cmdsocket,(struct sockaddr *) &client, &client_len)) == -1){
      printf("Error accepting client");
      exit(1);
    } else {
      printf("Client connected\n");
    }
    //datasocket
    //*******************************************************

    printf("Please filename to transfer: ");
    fgets(buf, BUFLEN, stdin);
    send (cmdsocket, buf, BUFLEN, 0);
    bzero(buf, BUFLEN);
    /*bf = buf;
    rd = BUFLEN;
    while ((n = recv(cmdsocket, bf, sizeof(buf), 0)) < 0){

    }
    printf ("sending:%s\n", buf);*
    string filename;
    cin >> filename;
    FILE *file;
    if((file=fopen(filename,"rb")) == NULL){
      printf("File doesn't exist");
    }

    //fill buffer with null characters
    memset(buf,'\0', BUFLEN);
    */


    }
