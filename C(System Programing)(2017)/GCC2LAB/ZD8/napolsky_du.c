#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <math.h>

#define BUFFERSIZE  4096
#define COPYMODE  0644

int main(int ac,char *av[])
{
   int option, divider=1, suminf=0;
   if((option=getopt(ac,av,"gkms"))!=-1)
      switch(option){
         case 'g':
            divider=1514362;
            break;
         case 'k':
            divider=2;
            break;
         case 'm':
            divider=2047;
            break;
         case 's':
            divider=0;
            break;
      }
   DIR *dir_ptr;
   struct dirent *direntp;
   dir_ptr=opendir(".");
   while((direntp=readdir(dir_ptr))!=NULL)
      if(direntp->d_name[0]!='.'){
           char *str = NULL;
           asprintf(&str, "./%s", direntp->d_name);
           struct stat info;
           stat(str, &info);
           divider?printf("%lld\t./%s\n", (info.st_blocks/divider)?info.st_blocks/divider:1, direntp->d_name):(suminf+=info.st_blocks);
      }
   closedir(dir_ptr);
   divider?divider:printf("%d\t.\n", suminf);
   return 0;
}
