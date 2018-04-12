#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFERSIZE  4096
#define COPYMODE  0644

int main(int ac,char *av[])
{
   if(geteuid()==0){
      fprintf(stderr,"Root permission is needed to execute that program\n");
      exit(1);
   }
   if(ac<2){
      fprintf(stderr,"Usage: %s <name of executable program>\n",*av);
      exit(1);
   }
   int option, passer=1, i=1;
   char temp[BUFFERSIZE];
   FILE *stringer;
   if((option=getopt(ac,av,"a:"))!=-1)
      switch(option){
         case 'a':
            option!=-1?i++:i;
            if(access(av[i],W_OK)!=-1) passer=0;
      }
   if(passer) fopen(av[i],"w");
   do{
      stringer=fopen(av[i],"a");
      fgets(temp,BUFFERSIZE,stdin);
      fprintf(stringer,"%s",temp);
      fclose(stringer);
      printf("%s",temp);
   }while(1);
   return 0;
}
