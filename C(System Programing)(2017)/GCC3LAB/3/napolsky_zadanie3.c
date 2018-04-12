#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char const *argv[]) {
   pid_t pid;
   pid=fork();
   switch (pid) {
      case -1:
         printf("Error\n");
         exit(1);
      case 0:
         //system("echo Today is:");
         execl("/bin/echo","echo","Today is:",NULL);
         break;
      default:
         //system("date");
         wait(pid);
         execl("/bin/date","date",NULL,NULL);
         break;
   }
   return 0;
}
