#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void catch_ctlc(int sig_num)
{
  printf("Ooooops! Nie zdarzyles!\n");
  fflush(stdout);
  exit(1);
}

int main(int ac, char *av[])
{
  int a=1;
  char haslo[3];
  signal(SIGALRM, catch_ctlc);
  printf("Masz tylko 5 sekund!\n");
  alarm(5);
  while (a){
     printf("Wprowadz haslo:\n");
     scanf("%s", haslo);
     fflush(stdout);
     a=strcmp(haslo,"123");
     printf(!a?"Access granted, all systems go!\n":"Access denied!\n");
     haslo[0]='\0';
  }

  return 0;
}
