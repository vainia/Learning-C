#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <pwd.h>
#include <sys/utsname.h>
#include <string.h>

void show_name(struct stat *buf){
    struct passwd *pwd;
    pwd = getpwuid(buf->st_uid);
    printf("Proces zostal urochomiony uzytkownikiem: %s\n", pwd->pw_gecos);
}

int main(int argc, char *argv[]) {
    struct stat info;
    int i=0;
    if(argc!=2){
        printf("Program pobiera tylko jeden argument jako nazwe procesu");
        exit(1);
    }
    char command[BUFSIZ], number[BUFSIZ], *pid;
    sprintf(command, "pidof %s", argv[1]);
    FILE *f = popen(command, "r");
    while (fgets(number, BUFSIZ, f) != NULL) i++;
    number[strlen(number)-1]=0;
    pid=strtok(number, " ");
    while (pid!=NULL)
    {
        command[0]='\0';
        sprintf(command, "/proc/%s", pid);
        pid=strtok(NULL, " ");
        if(stat(command, &info)!=-1) show_name(&info);
    }
    if(i==0) printf("Aplikacja \"%s\" nie jest uruchomiona\n", argv[1]);
    pclose(f);
    return 0;
}
