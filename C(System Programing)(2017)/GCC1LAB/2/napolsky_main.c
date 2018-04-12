#include <stdio.h>
int main (int argc, char *argv[])
{
  if(argc!=3){
  //if(argc<3){
      perror("error");
      fprintf(stderr,"musi byc dokladnie 2 argumenty");
      //fprintf(stderr,"musi byc co najmniej 2 argumenty");
      return 1;
}
else{
      printf("Urochomiony program: %s\n%s\n...\n%s\n",argv[0],argv[1],argv[2]);
}
return 0;
}
