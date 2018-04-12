#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

void mkprocif(long tgid, bool check) {
   char command[BUFSIZ];
   sprintf(command, "echo Process directory: /proc/%ld$\'\\n\'Current working directory: $(readlink /proc/%ld/cwd)$\'\\n\'\"Opened files (FD):\" $(readlink /proc/%ld/fd/*) >> %s; cat /proc/%ld/status >> %s;", tgid, tgid, tgid, check?"after":"before", tgid, check?"after":"before");
   system(command);
}

int main(int argc, char const *argv[]) {
   if (argc==2){
      long PID = atol(argv[1]);
      mkprocif(PID, true);
      char command[100];
      strcpy(command, "diff --new-line-format= --unchanged-line-format=\'%L\' --old-line-format= before after");
      system(command);
      remove("after");
      remove("before");
   } else {
      char PID[20];
      sprintf(PID, "%d", getpid());
      mkprocif(getpid(), false);
      execl("nuts"," ",PID,NULL);
   }
}
