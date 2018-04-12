#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
int main ()
{
   srand(time(NULL));
   time_t start,end;
   start = time (NULL);
   sleep(1+rand()%10);
   end = time (NULL);
   printf("\nSleep required:%2.f seconds\n", difftime(end, start));
   return 0;


return 0;
}
