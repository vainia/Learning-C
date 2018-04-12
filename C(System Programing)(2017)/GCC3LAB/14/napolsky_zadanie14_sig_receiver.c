#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

sig_atomic_t counter=0;
sig_atomic_t signame=0;
sig_atomic_t siglast=0;

void multi_handler(int sig, siginfo_t *siginfo, void *context) {
   pid_t sender_pid = siginfo->si_pid;
   if(siglast==sig) {
      kill((int)sender_pid, SIGKILL);
      printf("%d was recieved %d times\n", (int)signame, (int)signame==(int)siglast?(int)counter:(int)counter-1);
      exit(1);
   }
   if(!counter) siglast=sig;
   kill((int)sender_pid, SIGUSR1);
   ++counter;
   signame=sig;
}

int main(int argc, char const *argv[]) {
   if(argc!=2) {
      printf("program takes exactly 1 argument(only numeric): seconds to block sygnals\n");
   } else {
      struct sigaction signals;
      signals.sa_sigaction = *multi_handler;
      signals.sa_flags |= SA_SIGINFO;
      for(int i = 1; i < 32; i++) {
         sigaction(i, &signals, NULL);
      }
      for(;;) {
         pause();
      }
   }
   return 0;
}
