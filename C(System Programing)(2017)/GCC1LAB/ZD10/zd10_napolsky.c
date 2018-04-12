#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include  <pwd.h>
#include  <string.h>
#include  <sys/time.h>
#include  <time.h>
#include <stdlib.h>
#define SHOWHOST /* include remote machine on output */
void show_info(struct utmp*, int);
int main(int argc, char *argv[])
{
	struct utmp current_record; /* read info into here       */
	int utmpfd; /* read from this descriptor */
	int option=0;
	int reclen = sizeof(current_record);

	if ((utmpfd = open(UTMP_FILE, O_RDONLY))==-1)
	{
		perror(UTMP_FILE); /* UTMP_FILE is in utmp.h    */
		exit(1);
	}

	if (argc==3 && strcmp(argv[1],"am")==0 && strcmp(argv[2],"i")==0)
	{
		option=1;
	}

	while (read(utmpfd, &current_record, reclen) == reclen)
		show_info(&current_record, option);
	close(utmpfd);
	return 0; /* went ok */
}
/*
 *  show info()
 *	displays contents of the utmp struct in human readable form
 *	*note* these sizes should not be hardwired
 */
void showtime(int t)
{
	time_t time_ut=t;
	char timeString[256];
	struct tm* localTime=localtime(&time_ut);
	strftime(timeString,sizeof(timeString), "%b %d %H:%M", localTime);
	printf("    %s", timeString);
}

void show_i(struct utmp *bufput)
{
	printf("%-8.8s", bufput->ut_name); /* the logname	*/
	printf(" "); /* a space	*/
	printf("%-8.8s", bufput->ut_line); /* the tty	*/
	printf(" "); /* a space	*/
	showtime(bufput->ut_time); /* login time	*/
	printf(" "); /* a space	*/
	#ifdef SHOWHOST
	printf("(%s)", bufput->ut_host); /* the host	*/
	#endif
	printf("\n"); /* newline	*/
}
void show_info(struct utmp *utbufp, int option)
{
	if (option==1) {
		if (strcmp(utbufp->ut_name,getlogin())==0)
		{
			show_i(&*utbufp);
		}
	} else
	{
		if (utbufp->ut_type==USER_PROCESS)
		{
			show_i(&*utbufp);
		}
	}
}
