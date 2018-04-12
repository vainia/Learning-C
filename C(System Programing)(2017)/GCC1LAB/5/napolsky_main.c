#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/time.h>
#include <time.h>

int main ()
{
time_t rawtime;
time(&rawtime);
printf("Date:%s\n",ctime(&rawtime));
char timeString[256];
struct tm* localTime = localtime(&rawtime);
printf("LocalTime\n");
strftime(timeString,sizeof(timeString), "%d.%m.%Y %H", localTime);
printf("%s\n\n", timeString);
struct tm* gmTime= gmtime(&rawtime);
printf("gmTime\n");
strftime(timeString,sizeof(timeString), "%d.%m.%Y %H", gmTime);
printf("%s\n", timeString);

return 0;
}
