#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <pwd.h>
#include <unistd.h>
#include <sys/wait.h>

void rmprocif(long tgid) {
   char ID[20];
   sprintf(ID, "%ld", tgid);
   remove(ID);
}

void mkprocif(long tgid) {
   FILE *fpro;
   char filen[20];
   sprintf(filen, "%ld", tgid);
   fpro = fopen(filen, "a");
   int counter=0;
   char path[20], line[BUFSIZ];
   fprintf(fpro, "Process directory: /proc/%ld\n", tgid);
   char command[BUFSIZ], cwd[BUFSIZ], fd[BUFSIZ];
   sprintf(command, "readlink \"/proc/%ld/cwd\"", tgid);
   FILE *f = popen(command, "r");
   fgets(cwd, BUFSIZ, f);
   fprintf(fpro, "Current working directory: %s", cwd);
   pclose(f);
   command[0]='\0';
   sprintf(command, "readlink \"/proc/%ld/fd/\"*", tgid);
   FILE *f2 = popen(command, "r");
   while (fgets(fd, BUFSIZ, f2)){
      fd[strlen(fd)-1]=0;
      fprintf(fpro, (counter++)==0?"Opened files (FD): %s":", %s", fd);
   };
   fprintf(fpro, "\n");
   pclose(f2);
   FILE* statusf;
   snprintf(path, 20, "/proc/%ld/status", tgid);
   statusf = fopen(path, "r");
   if(!statusf) return;
   while(fgets(line, 200, statusf)) fprintf(fpro, "%s", line);
   fclose(statusf);
   fclose(fpro);
}

int main(int argc, char const *argv[]) {
   pid_t pid;
   pid=fork();
   if(pid==-1) {
      printf("Error\n");
      exit(1);
   } else if(pid==0) {
      mkprocif(getpid());
      mkprocif(getppid());
      char command[100];
      strcpy(command, "diff --new-line-format= --unchanged-line-format=\'%L\' --old-line-format= ");
      sprintf(command + strlen(command), "%d %d", getppid(), getpid());
      printf("_________________________________________________________________\nAtrubyty dziedziczone\n_________________________________________________________________\n");
      system(command);
      command[0]='\0';
      strcpy(command, "diff --new-line-format=\'%L\' --unchanged-line-format= --old-line-format= ");
      sprintf(command + strlen(command), "%d %d", getppid(), getpid());
      printf("_________________________________________________________\nAtrubyty z nowymi wartosciami\n_________________________________________________________\n");
      system(command);
      rmprocif(getpid());
      rmprocif(getppid());
   } else {
      wait(NULL);
   }
}
