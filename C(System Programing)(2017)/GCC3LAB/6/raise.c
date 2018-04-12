#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

void usr1_handler( int sig_num )
{

  printf( "Rodzic (%d) otrzymal sygnal %d\n", getpid(), sig_num);

}

int main()
{
  pid_t ret;
  int   status;
  int   role = -1;

  ret = fork();
  if (ret > 0) {
    printf( "Rodzic: to jest proces macierzysty (pid %d)\n",
             getpid() );
    signal( 2, usr1_handler );
    role = 0;
    pause();
    printf( "Rodzic: czekam na zakonczenie potomka\n" );
    ret = wait( &status );
  }
  else if (ret == 0) {
    printf( "Potomek: to jest proces potomny (pid %d)\n",
             getpid() );
    role = 1;
    sleep( 1 );
    printf( "Potomek: Wysylam 2 do pid %d\n", getppid() );
    kill( getppid(), 2 );
    sleep( 2 );

  }
  else {
    printf( "Rodzic: Blad podczas proby wykonania fork() (%d)\n", errno );

  }

  printf( "%s: Koncze ...\n",
           ((role == 0) ? "Rodzic" : "Potomek") );

  return 0;
}
