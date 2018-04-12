#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <pwd.h>
#include <string.h>
#include <stdlib.h>

void show_info(struct utmp *utbufp)
{
	if (utbufp->ut_type==USER_PROCESS)
	{
		char *login=utbufp->ut_name;
		struct passwd *opis;
	   if((opis=getpwnam(login))==NULL)
		{
	           perror("getpwnam");
	   } else
		{
			printf("\nuser name: %s\n", opis->pw_name);
			printf("UID : %d\n", opis->pw_uid);
			printf("GID : %d\n", opis->pw_gid);
			printf("gecos : %s\n", opis->pw_gecos);
			printf("home dir : %s\n", opis->pw_dir);
			printf("shell : %s\n", opis->pw_shell);
		}
	}
}

void fusr()
{
	struct utmp current_record;
	int utmpfd;
	int reclen = sizeof(current_record);
	if ((utmpfd = open(UTMP_FILE, O_RDONLY))==-1)
	{
		perror(UTMP_FILE);
		exit(1);
	}
	while (read(utmpfd, &current_record, reclen) == reclen)
		show_info(&current_record);
	close(utmpfd);
}
