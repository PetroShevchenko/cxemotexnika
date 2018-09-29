//tcp_client.c
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <fcntl.h>
#include <netdb.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

#define PORTNUM 1500

int main(int argc, char ** argv)
{
	int s;
	int pid;
	int i,j;
	struct sockaddr_in serv_addr;
	struct hostent *hp;
	char buf[80]="Hello, NUCLEO_F429ZI board!";

	if((hp=gethostbyname(argv[1]))==0) {
		perror("socket() error");
		exit(3);
	}

	bzero(&serv_addr, sizeof(serv_addr));
	bcopy(hp->h_addr, &serv_addr.sin_addr, hp->h_length);
	serv_addr.sin_family=hp->h_addrtype;
	serv_addr.sin_port=htons(PORTNUM);

	if((s=socket(AF_INET, SOCK_STREAM, 0))==-1){
		perror("socket() error");
		exit(1);
	}

	fprintf(stderr, "Address of server is %s\n", inet_ntoa(serv_addr.sin_addr));

	if(connect(s, (struct sockaddr *)&serv_addr, sizeof(serv_addr))==-1) {
		perror("connect() error");
		exit(1);
    }
    send(s, buf, sizeof(buf), 0);

    if(recv(s, buf, sizeof(buf), 0) < 0) {
    	perror("recv() error");
    	exit(1);
    }
    printf("Received from server : %s\n", buf);
    close(s);
    printf("client have done its work\n\n");
    return 0;
}