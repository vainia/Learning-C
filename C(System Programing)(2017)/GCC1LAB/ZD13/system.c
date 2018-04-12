#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/utsname.h>

void fsys()
{
	struct utsname utsname;
	if (uname (&utsname) != -1) {
			  printf ("\nInfo from uname:\n");
			  printf (" sysname: %s\n", utsname.sysname);
			  printf (" nodename: %s\n", utsname.nodename);
			  printf (" release: %s\n", utsname.release);
			  printf (" version: %s\n", utsname.version);
			  printf (" machine: %s\n\n", utsname.machine);
	}
}
