#include "lwip.h"
#include "sockets.h"
#include "netdb.h"
#include "cmsis_os.h"
#include <string.h>
#include "tcp_socket_client.h"

#define PORTNUM 1500
#define SERVER_IP "192.168.0.100"

static struct sockaddr_in serv_addr;
static struct hostent *hp;
static char buf[80];//="Hello, NUCLEO_F429ZI board!";


static int tcp_socket_client_send_message(const char *message)
{
	int socket_fd;

	if(strlen(message)>80) {
	   perror("too long size of string(>80)\n");
	   return -1;
	}

	strcpy(buf,message);


	if((hp= gethostbyname(SERVER_IP))==0) {
		perror("gethostbyname() error\n");
		return -1;
	}

	bzero(&serv_addr, sizeof(serv_addr));
	bcopy(hp->h_addr, &serv_addr.sin_addr, hp->h_length);

	serv_addr.sin_family=hp->h_addrtype;
	serv_addr.sin_port=htons(PORTNUM);

	if((socket_fd=socket(AF_INET, SOCK_STREAM, 0))==-1){
		perror("socket() error\n");
		return -1;
	}

	printf("Address of server is %s\n", inet_ntoa(serv_addr.sin_addr));

	if(connect(socket_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))==-1) {
		perror("connect() error\n");
		close(socket_fd);
		return -1;
    }
    send(socket_fd, buf, sizeof(buf), 0);

    if(recv(socket_fd, buf, sizeof(buf), 0) < 0) {
    	perror("recv() error\n");
    	close(socket_fd);
    	return -1;
    }
    printf("Received from server : %s\n", buf);
    close(socket_fd);
    printf("client have done its work\n\n");
    return 0;
}


void StartTcpSocketClientTask(void const * argument)
{
	osEvent event;

	MX_LWIP_Init();

	for(;;)
	{
		 event = osSignalWait (SIGNAL_PUSH_BUTTON, osWaitForever);

		 if (event.status == osEventSignal)  {
			 if(tcp_socket_client_send_message("Hello, NUCLEO_F429ZI!")< 0) {
				 printf("tcp_socket_client_send_message() error\n");
			 }
		 }
		 else {
			 printf("osSignalWait() error\n");
		 }
	}

}

