#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

void catch_ctlc( int sig_num )
{
  printf( "Przechwycono Control-C\n" );
  fflush( stdout );

  return;
}

int main()
{
  signal( 2, catch_ctlc );

  printf("Dzialam ...\n");

  pause();

  return 0;
}
