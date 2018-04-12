#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
   if(argc!=2||atoi(argv[1])<1){
      printf("Please set N (count of iteractions) as taken argument of program\n");
      exit(0);
   }
   pid_t pid;
   pid=fork();
   for (int i=0; i<atoi(argv[1]); i++) {
      switch (pid) {
         case -1:
            printf("Error\n");
            exit(1);
         case 0:
            for (char x='a'; x <= 'z'; x++) {
               printf("%c", x);
            }
            break;
         default:
            for (char x='A'; x <= 'Z'; x++) {
               printf("%c", x);
            }
            break;
      }
   }
   return 0;
}
