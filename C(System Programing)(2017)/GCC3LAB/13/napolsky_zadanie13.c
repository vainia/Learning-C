#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <pwd.h>

int print_proc(long tgid) {
    char path[20], line[40], *p;
    FILE* statusf;
    snprintf(path, 20, "/proc/%ld/status", tgid);
    statusf = fopen(path, "r");
    if(!statusf) return 0;
    while(fgets(line, 40, statusf)) {
        if(strncmp(line, "Name:", 5) != 0) continue;
        p = line + 6;
        while(isspace(*p)) ++p;
        printf("%li %s", tgid, p);
        break;
    }
    fclose(statusf);
    return 1;
}

int compare_name(struct stat *buf, long tgid, const char *user) {
    struct passwd *pwd;
    pwd = getpwuid(buf->st_uid);
    if(strcmp(pwd->pw_name, user) == 0) return print_proc(tgid);
    return 0;
}

int main(int argc, char const *argv[]) {
   if(argc!=2){
      printf("Program pobiera tylko jeden argument jako nazwe uzytkownika");
      exit(1);
   }
   DIR* proc = opendir("/proc");
   if(proc == NULL) {
       perror("opendir(/proc)");
       return 1;
   }
   struct dirent* ent;
   long tgid;
   char path[BUFSIZ];
   struct stat info;
   int any=0;
   while((ent = readdir(proc))) {
       if(!isdigit(*ent->d_name))
           continue;
       tgid = strtol(ent->d_name, NULL, 10);
       sprintf(path, "/proc/%ld", tgid);
       if(stat(path, &info)!=-1) any+=compare_name(&info,tgid,argv[1]);
   }
   if(any==0) printf("Uzytkownik %s nie urochomil zadnego procesu!\n", argv[1]);
   closedir(proc);
   return 0;
}
