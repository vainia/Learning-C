#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>

int main(int argc, char *argv[]){
   int option, polesco=1, limiter, rowco=12, timeinsec=360; //argument "timeinsec" holds time of file observation
   struct stat info;
   if(argc<2||argc>4||argc==3||(argc==4&&(atoi(argv[2])>30||atoi(argv[2])<1||timeinsec%atoi(argv[2])!=0))){
      fprintf(stderr,"Usage: %s [-t <number of columns wich lower than 30 and divvy %d without remainder>] <file name>\n", *argv, timeinsec);
      exit(1);
   }
   if((option=getopt(argc,argv,"t:"))!=-1)
      switch(option){
         case 't':
            polesco=0;
      }
   if(access(option!=-1?argv[3]:argv[1],F_OK)==-1){
      fprintf(stderr,"File \"%s\" does not exist\n", option!=-1?argv[3]:argv[1]);
      exit(2);
   }
   polesco=(polesco==0)?atoi(argv[2]):10;
   unsigned long long allfsize[polesco], maxfsize;
   limiter=timeinsec/polesco;
   for(int i=limiter;i<=limiter*polesco;i+=limiter){
      sleep(limiter);
      stat(option!=-1?argv[3]:argv[1], &info);
      allfsize[i/limiter]=info.st_size;
      if(i==limiter){
         maxfsize=info.st_size;
      }else if(maxfsize<info.st_size)
         maxfsize=info.st_size;
      printf("time elapsed: %d seconds, current file size: %lld bytes\n", (timeinsec/polesco)*(i/limiter), info.st_size);
   }
   printf("^\n");
   for(int i=1; i<=rowco; i++){
      printf("|");
      for(int ii=1; ii<=polesco; ii++){
         printf(" %-2s", maxfsize/i>allfsize[ii]?"░":"█");
      }
      i==1?printf("\t%llu", maxfsize/i):i==2?printf("\t%.0f-%llu", maxfsize/(i-0.5), maxfsize/(i-1)-1):printf("\t%.0f-%.0f", maxfsize/(i-0.5), maxfsize/(i-1.5)-1);
      printf("\n");
   }
   printf("+");
   for(int iii=1; iii<=polesco; iii++)
      printf("--");
   printf(">\n");
}
