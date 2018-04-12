#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <pwd.h>
#include <sys/utsname.h>
#include <string.h>

void show_name(char *procnam, struct stat *buf){
    struct passwd *pwd;
    pwd = getpwuid(buf->st_uid);
    printf("Proces \"%s\" zostal urochomiony uzytkownikiem: %s\n", procnam, pwd->pw_gecos);
}

void pid_info(char *procnam){
    int i=0;
    struct stat info;
    char command[BUFSIZ], number[BUFSIZ], *pid, *rest=number;
    sprintf(command, "pidof %s", procnam);
    FILE *f = popen(command, "r");
    while (fgets(number, BUFSIZ, f) != NULL) i++;
    number[strlen(number)-1]=0;
    while ((pid = strtok_r(rest, " ", &rest))){
        sprintf(command, "/proc/%s", pid);
        if(stat(command, &info)!=-1) show_name(procnam, &info);
    }
    if(i==0) printf("Aplikacja \"%s\" nie jest uruchomiona\n", procnam);
    pclose(f);
}

int main(int argc, char *argv[]) {
    if(argc!=2){
        printf("Program pobiera tylko jeden argument jako nazwe pliku tekstowego\n");
        printf("!!!!!!!!!!Nazwy procesow musa byc rozdzielone spacjami!!!!!!!!!!\n");
        exit(1);
    }
    char str[BUFSIZ], *stid;
    FILE *file=fopen(argv[1],"r");
    if (file){
         if (fgets(str, BUFSIZ, file)==NULL) printf("Plik \"%s\" jest pusty\n", argv[1]);
         str[strlen(str)-1]=0;
         for (stid=strtok(str, " ");stid;stid=strtok(NULL, " ")) pid_info(stid);
         fclose(file);
    } else printf("Plik \"%s\" nie istnieje\n", argv[1]);
    return 0;
}
