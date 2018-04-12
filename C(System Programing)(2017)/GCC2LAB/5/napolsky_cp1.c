#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define BUFFERSIZE  4096
#define COPYMODE  0644

void err(char *,char *);

int main(int ac,char *av[])
{
  int option,in_fd,out_fd,n_chars,passer=1;
  char buf[BUFFERSIZE],answer[1];
  if(ac<3||ac>4){
    fprintf(stderr,"usage: %s [-i] source destination\n",*av);
    exit(1);
  }

  if((option=getopt(ac,av,"i:"))!=-1){
     switch(option){
        case 'i':
         if(access(av[3],F_OK)!=-1){
            passer=0;
         }
     }
  }

  int i=1;
  option!=-1?i++:i;

  if((in_fd=open(av[i],O_RDONLY))==-1)
  err("Cannot open ",av[i]);

  if(!passer){
     printf("overwrite \"%s\"? (y/n)\n",av[3]);
     scanf("%s",answer);
     if(!strcmp(answer,"n")){
     }else if(strcmp(answer,"y")){
        printf("not overwritten\n");
     }else{
        passer=1;
     }
  }

  if(passer){
     if((out_fd=creat(av[i+1],COPYMODE))==-1)
      err("Cannot creat",av[i+1]);

     while((n_chars=read(in_fd,buf,BUFFERSIZE))>0)
      if(write(out_fd,buf,n_chars)!=n_chars)
          err("Write error to ",av[i+1]);

     if(n_chars==-1)
             err("Read error from ",av[i]);

     if(close(in_fd)==-1||close(out_fd)==-1)
      err("Error closing files","");
     exit(0);
  }
}

void err(char *s1,char *s2){
  fprintf(stderr,"Error: %s ",s1);
  perror(s2);
  exit(1);
}
