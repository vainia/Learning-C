#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>

#define MAX_BUFFER 128
#define TIME_SERVER_PORT 37

void myTime(int connectionFd);

int main (int argc, char *argv[] )
{
  int connectionFd;
  int port;
  struct sockaddr_in servaddr;
 
  if ((argc < 2) || (argc > 3)) {
    fprintf(stderr,"Usage: %s <Server IP> [<Time Port>]\n",
            argv[0]);
    exit(1);
  }

  if (argc == 3)
    port=atoi(argv[2]);
  else
    port=TIME_SERVER_PORT;

  errno = 0;
  connectionFd = socket(PF_INET, SOCK_STREAM, 0);
  if (connectionFd == -1)
  {
    perror("socket() error");
    exit(1);
  }

  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(port);

  servaddr.sin_addr.s_addr = inet_addr(argv[1]);

  errno = 0;
  if (connect(connectionFd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
  {
    perror("connect() error");
    exit(1);
  }

  myTime(connectionFd);

  return(0);
}
void myTime(int connectionFd)
{
	int in;
	time_t czas;
	in = read(connectionFd, &czas, sizeof(time_t));
	if (in != sizeof(time_t))
	{
		printf("blad read()\n");
		exit(1);
	}
	czas = ntohl(czas) - 2208988800UL;
	if (close(connectionFd) == -1)
	{
		perror("close() error");
		exit(1);
	}
	printf("Czas pobrany z serwera: %s\n", ctime(&czas));
}
