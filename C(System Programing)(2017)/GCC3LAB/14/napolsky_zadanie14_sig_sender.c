#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int sig) {}

int main(int argc, char const *argv[]) {
   if(argc!=5){
      printf("program takes exactly 4 arguments(only numeric): PID, signal, count of signals, signal-killer\n");
   } else {
      kill(atoi(argv[1]), atoi(argv[4]));
      signal(SIGUSR1, handler);
      for (int i=0; i<atoi(argv[3]); i++) {
         pause();
         kill(atoi(argv[1]), atoi(argv[2]));
      }
      pause();
      kill(atoi(argv[1]), atoi(argv[4]));
   }
   return 0;
}
