#include <stdlib.h>
#include <stdio.h>

struct {
    char    *abbrev;
    char    *fullname;
} days[] = {
    {"Mon",  "Monday"},
    {"Tue",  "Tuesday"},
    {"Wed",  "Wednesday"},
    {"Thu",  "Thursday"},
    {"Fri",  "Friday"},
    {"Sat",  "Saturday"},
    {"Sun",  "Sunday"},
    {0,      0}
};

int main(void)
{
    int i;
    int status;
    char command[BUFSIZ];

    for (i=0; days[i].abbrev != NULL; i++) {
      sprintf(command, "[ $(date|awk '{print $1}') == '%s' ]", days[i].abbrev);
      status = system(command);
      switch ((status >> 8) & 0xff) {
        case 0:
            printf("Today is %s.\n", days[i].fullname);
            break;
        case 1:
            printf("Today is not %s.\n", days[i].fullname);
            break;
        case 2:
            printf("Error in pattern specification.\n");
            exit(1);
      }
    }

    exit(0);
}
