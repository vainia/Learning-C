#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>

void print_status(char *tgid) {
   int counter=0;
   char path[20], line[BUFSIZ];
   printf("Process directory: /proc/%s\n", tgid);
   char command[BUFSIZ], cwd[BUFSIZ], fd[BUFSIZ];
   sprintf(command, "readlink \"/proc/%s/cwd\"", tgid);
   FILE *f = popen(command, "r");
   fgets(cwd, BUFSIZ, f);
   printf("Current working directory: %s", cwd);
   pclose(f);
   command[0]='\0';
   sprintf(command, "readlink \"/proc/%s/fd/\"*", tgid);
   FILE *f2 = popen(command, "r");
   while (fgets(fd, BUFSIZ, f2)){
      fd[strlen(fd)-1]=0;
      printf((counter++)==0?"Opened files: %s":", %s", fd);
   };
   printf("\n");
   pclose(f2);
   FILE* statusf;
   snprintf(path, 20, "/proc/%s/status", tgid);
   statusf = fopen(path, "r");
   if(!statusf) return;
   while(fgets(line, 200, statusf)) printf("%s", line);
   printf("###########################################################\n");
   fclose(statusf);
}

int main(int argc, char const *argv[]) {
   int i=0;
   if(argc!=2){
      printf("Program pobiera tylko jeden argument jako nazwe procesu");
      exit(1);
   }
   char command[BUFSIZ], number[BUFSIZ], *pid;
   sprintf(command, "pidof %s", argv[1]);
   FILE *f = popen(command, "r");
   while (fgets(number, BUFSIZ, f) != NULL) i++;
   number[strlen(number)-1]=0;
   pid=strtok(number, " ");
   while (pid!=NULL)
   {
      command[0]='\0';
      print_status(pid);
      pid=strtok(NULL, " ");
   }
   if(i==0) printf("Aplikacja \"%s\" nie jest uruchomiona\n", argv[1]);
   pclose(f);
   return 0;
}
