#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFERSIZE  4096

void err(char *,char *);

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
   char *dup=strdup(getenv("PATH"));
   char *s=dup;
   char *p=NULL;
   do{
       p=strchr(s, ':');
       if(p!= NULL) p[0]=0;
       char *str = NULL;
       asprintf(&str, "%s/%s", s,av[1]);
       if(access(str,F_OK)!=-1) printf("%s\n",str);
       s=p+1;
   }while(p!=NULL);
   free(dup);
   return 0;
}
