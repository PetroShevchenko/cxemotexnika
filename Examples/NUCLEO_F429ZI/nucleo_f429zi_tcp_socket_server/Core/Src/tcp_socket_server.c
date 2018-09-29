#include "lwip.h"
#include "sockets.h"
#include "cmsis_os.h"
#include <string.h>

#define PORTNUM 1500

static struct sockaddr_in serv_addr, client_addr;
static int socket_fd;
static uint16_t nport;


void ServerThread(void const * argument);

const osThreadDef_t os_thread_def_server1 = { "Server1", ServerThread, osPriorityNormal, 0, 256};
const osThreadDef_t os_thread_def_server2 = { "Server2", ServerThread, osPriorityNormal, 0, 256};
const osThreadDef_t os_thread_def_server3 = { "Server3", ServerThread, osPriorityNormal, 0, 256};
const osThreadDef_t os_thread_def_server4 = { "Server4", ServerThread, osPriorityNormal, 0, 256};
const osThreadDef_t os_thread_def_server5 = { "Server5", ServerThread, osPriorityNormal, 0, 256};

const osThreadDef_t * Servers[5] = {&os_thread_def_server1, &os_thread_def_server2, &os_thread_def_server3, &os_thread_def_server4, &os_thread_def_server5};
osThreadId ThreadId[5] = {NULL, NULL, NULL, NULL, NULL};


static int tcpSocketServerInit(void)
{
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd == -1) {
		perror("socket() error\n");
		return -1;
	}

	nport = PORTNUM;
	nport = htons((uint16_t)nport);

	bzero(&serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = nport;

	if(bind(socket_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))==-1) {
		perror("bind() error\n");
		close(socket_fd);
		return -1;
	}

	printf("Server is ready: %s\n", inet_ntoa(serv_addr.sin_addr));

	if(listen(socket_fd, 5) == -1) {
		perror("listen() error\n");
		close(socket_fd);
		return -1;
	}

	return 0;
}

void StartTcpSocketServerTask(void const * argument)
{
    int accept_fd;
	int addr_len;
	int i = 0;

	MX_LWIP_Init();

	if(tcpSocketServerInit() < 0) {
		return;
	}

	for(;;)
	{
		  bzero(&client_addr, sizeof(client_addr));
		  addr_len = sizeof(client_addr);

		  accept_fd = accept(socket_fd, (struct sockaddr *)&client_addr, (socklen_t *)&addr_len);

		  if (accept_fd == -1) {
			  perror("accept() error\n");
			  close(socket_fd);
			  while(1) {osThreadTerminate(NULL);}
		  }

		  printf("Client = %s\n", inet_ntoa(client_addr.sin_addr));
		  printf("accept_fd = %d\n", accept_fd);

		  //create a new thread
		  printf("osThreadCreate(%d)\n", i);

		  if (ThreadId[i] != NULL) {
			  osDelay(10);
			  while(1) {osThreadTerminate(ThreadId[i]);}
		  }

		  ThreadId[i] = osThreadCreate (Servers[i], &accept_fd);
		  i++;

		  if (i > 4) {
			  i = 0;
		  }

	}
}


void ServerThread(void const * argument)
{
	int accept_fd = *((int *)argument);
	int nbytes;
	char buffer[80];
	osThreadId id;
	int i;

	printf("ServerThread(%d) is started\n",accept_fd);
	for(;;)
	{

	  while ( (nbytes = recv(accept_fd, buffer, sizeof(buffer), 0)) != 0 )
	  {
		  send(accept_fd, buffer, sizeof(buffer), 0);
	  }

	  //osDelay(10000);
	  printf("ServerThread(%d) is done\n",accept_fd);
	  close(accept_fd);

	  id = osThreadGetId ();
	  for(i = 0; i < 5; i++)
	  {
		  if (ThreadId[i] == id) {
			  ThreadId[i] = NULL;
			  break;
		  }
	  }

	  while(1) {osThreadTerminate(NULL);}
	}
}
