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

#define BUFLEN			80  	// Buffer length

int main (int argc, char *argv[]) {
    struct hostent	*hp;
    struct sockaddr_in server;
    char *bf, buf[BUFLEN];
    int port, cmdsocket;
    char *host;
    string msg;
    int n, read;

      if(argc != 2){
        printf("Error : host [port]");
        exit(1);
      } else {
        host = argv[0];
        port = atoi(argv[1]);
      }


    //create command socket, returns socket file descriptor(int)
    if ((cmdsocket = socket(AF_INET, SOCK_STREAM,0)) == -1){
      printf("Error creating socket");
      exit(1);
    } else {

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
      printf("Error connectiong to server");
      exit(1);
    } else {
      printf("Connected to server");
    }

    printf("Please enter a message to send to the server: ");
    //cin >> msg;
    fgets(buf, BUFLEN, stdin);
    send (cmdsocket, buf, BUFLEN, 0);
    bzero(buf, BUFLEN);
    bf = buf;
    read = BUFLEN;
    while ((n = recv(cmdsocket, bf, sizeof(buf), 0)) < 0){

    }
    printf ("sending:%s\n", buf);
}
