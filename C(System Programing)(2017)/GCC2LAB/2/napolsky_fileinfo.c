#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

void show_stat_info(char *fname, struct stat *buf);
void sprawdz(char *nazwa_pliku);

int main(int argc, char *argv[])
{
    struct stat info;
    if (argc>1) {
      if( stat(argv[1], &info) != -1 ){
            show_stat_info( argv[1], &info );
            return 0;
      }
    }
    else
      printf("Uzycie: %s nazwa_pliku\n",argv[0]);
    return 1;

}

char* formatdate(char* str, time_t val)
{
strftime(str, 36, "%d.%m.%Y %H:%M:%S", localtime(&val));
return str;
}

void show_stat_info(char *fname, struct stat *buf)
{
    printf("File name: %s\n", fname );
    sprawdz(fname);
    strcpy( fname, "----------" ); /* default=no perms */
    if ( S_ISDIR(buf->st_mode) ) fname[0] = 'd'; /* directory */ 
    if ( S_ISCHR(buf->st_mode) ) fname[0] = 'c'; /* char devices */
    if ( S_ISBLK(buf->st_mode) ) fname[0] = 'b'; /* block device */
    if ( buf->st_mode & S_IRUSR ) fname[1] = 'r'; /* 3 bits for user */
    if ( buf->st_mode & S_IWUSR ) fname[2] = 'w';
    if ( buf->st_mode & S_IXUSR ) fname[3] = 'x';
    if ( buf->st_mode & S_IRGRP ) fname[4] = 'r'; /* 3 bits for group */
    if ( buf->st_mode & S_IWGRP ) fname[5] = 'w';
    if ( buf->st_mode & S_IXGRP ) fname[6] = 'x';
    if ( buf->st_mode & S_IROTH ) fname[7] = 'r'; /* 3 bits for other */
    if ( buf->st_mode & S_IWOTH ) fname[8] = 'w';
    if ( buf->st_mode & S_IXOTH ) fname[9] = 'x';
    printf("Mode: %s\n", fname);
    printf("Links: %ld\n", buf->st_nlink);        /* # links     */
    
    
    struct group *grp;
    struct passwd *pwd;

    grp = getgrgid(buf->st_gid);
    printf("group: %s\n", grp->gr_name);

    pwd = getpwuid(buf->st_uid);
    printf("username: %s\n", pwd->pw_name);

    //printf("UID: %d\n", buf->st_uid);          /* user id     */
    //printf("GID: %d\n", buf->st_gid);          /* group id    */
    
    printf("Size: %ld\n", buf->st_size);         /* file size   */
    
    char date[36];
    formatdate(date, buf->st_atime);
    printf("Access: %s\n", date);
    formatdate(date, buf->st_mtime);
    printf("Modify: %s\n",date);
    formatdate(date, buf->st_ctime);
    printf("Change: %s\n", date);

}

void sprawdz(char *nazwa_pliku) {
    struct stat buf;
    char *ptr;
    lstat(nazwa_pliku,&buf);
    if (S_ISREG(buf.st_mode)) ptr = "zwykly";
        else if (S_ISDIR(buf.st_mode)) ptr = "katalog";
        else if (S_ISCHR(buf.st_mode)) ptr = "specjalny znakowy";
        else if (S_ISBLK(buf.st_mode)) ptr = "specjalny blokowy";
        else if (S_ISFIFO(buf.st_mode)) ptr = "fifo";
    #ifdef S_ISLNK
    else if (S_ISLNK(buf.st_mode)) ptr = "dowiazanie";
    #endif 
    #ifdef S_ISSOCK
    else if (S_ISSOCK(buf.st_mode)) ptr = "gniazdo";
    #endif
    else ptr = "** nieznany typ pliku **";
    printf("File type: %s\n", ptr);
}
