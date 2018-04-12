#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void catch_ctlc( int sig_num )
{
  printf( "Przechwycilem sygnal!\n" );
  fflush( stdout );

  return;
}

int main(int ac, char *av[])
{

  signal( SIGINT, catch_ctlc );

  for (;;){
     printf("Dzialam dalej\n");
     sleep(ac==2?atoi(av[1]):1);
  }

  return 0;
}
