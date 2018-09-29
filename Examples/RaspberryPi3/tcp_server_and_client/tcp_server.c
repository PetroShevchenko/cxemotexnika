//tcp_server.c

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
	int s, ns;
	int pid;
	int nport;
	struct sockaddr_in serv_addr, clnt_addr;
	struct  hostent *hp;
	char buf[80], hname[80];
	nport = PORTNUM;
	nport = htons((u_short)nport);

	if((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket() error");
		exit(1);
	}

	bzero(&serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = nport;

	if(bind(s, (struct sockaddr *)&serv_addr, sizeof(serv_addr))==-1) {
		perror("bind() error");
		exit(1);
	}

	fprintf(stderr, "server ready: %s\n", inet_ntoa(serv_addr.sin_addr));

	if (listen(s,5) == -1) {
		perror("listen() error");
		exit(1);
	}

	while(1)
	{

		int addrlen;

		bzero(&clnt_addr, sizeof(clnt_addr));
		addrlen = sizeof(clnt_addr);

		if ((ns = accept(s, (struct sockaddr *)&clnt_addr, &addrlen))==-1) {
			perror("accept() error");
			exit(1);
		}

		fprintf(stderr, "Client = %s\n", inet_ntoa(clnt_addr.sin_addr));

		if((pid=fork())==-1) {
			perror("fork() error");
			exit(1);
		}

		if(pid==0) {
			int nbytes;
			int fout;

			close(s);
			while((nbytes = recv(ns, buf, sizeof(buf), 0))!=0) {
				send(ns, buf, sizeof(buf), 0);				
			}
			close(ns);
			exit(0);
		}

		close(ns);
	}
	return 0;
} 
