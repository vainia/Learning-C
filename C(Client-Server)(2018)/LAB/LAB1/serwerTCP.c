/*
 *  Daytime Server (TCP)
 */

#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define MAX_BACKLOG     5
#define MAX_BUFFER      128

void HandleClient(int connectionFd);

int main ( int argc, char *argv[])
{
  int serverFd, connectionFd;
  struct sockaddr_in servaddr;
  int daytimePort;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <Server Port>\n", argv[0]);
    exit(1);
  }
  daytimePort=atoi(argv[1]);

  errno = 0;
  serverFd = socket(AF_INET, SOCK_STREAM, 0);
  if (serverFd == -1)
  {
    perror("socket() error");
    exit(1);
  }

  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(daytimePort);

  errno = 0;
  if (bind(serverFd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
  {
    perror("bind() error");
    exit(1);
  }

  errno = 0;
  if (listen(serverFd, MAX_BACKLOG) == -1)
  {
    perror("listen() error");
    exit(1);
  }

  while ( 1 ) {

    errno = 0;
    connectionFd = accept(serverFd, 
                           (struct sockaddr *)NULL, NULL);
    if (connectionFd >= 0) {
      HandleClient(connectionFd);
    } else {
      perror("accept() error");
      exit(1);
    }
  }
}
void HandleClient(int connectionFd)
{
  char timebuffer[MAX_BUFFER+1];
  time_t currentTime;
  currentTime = time(NULL);
  snprintf(timebuffer, 
           MAX_BUFFER, "%s\n", ctime(&currentTime));
  errno = 0;
  if (write(connectionFd, timebuffer, strlen(timebuffer)) == -1)
  {
    perror("write() error");
    exit(1);
  }
  errno = 0;
  if (close(connectionFd) == -1)
  {
    perror("close() error");
    exit(1);
  }
}
