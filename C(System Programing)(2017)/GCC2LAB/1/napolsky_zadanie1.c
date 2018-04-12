#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

void show_stat_info(char *str, struct stat *buf);

int main(int argc, char *argv[])
{
    struct stat info;
    if (argc>1) {
      if( stat(argv[1], &info) != -1 ){
            show_stat_info( argv[1], &info );
            return 0;
      }
      else
          printf("Plik nie istnieje\n");
    }
    else
      printf("Uzycie: %s nazwa_pliku\n",argv[0]);
    return 1;
}

void show_stat_info(char *str, struct stat *buf)
{
    strcpy( str, "----------" ); /* default=no perms */
    if ( S_ISDIR(buf->st_mode) ) str[0] = 'd'; /* directory */ 
    if ( S_ISCHR(buf->st_mode) ) str[0] = 'c'; /* char devices */
    if ( S_ISBLK(buf->st_mode) ) str[0] = 'b'; /* block device */
    if ( buf->st_mode & S_IRUSR ) str[1] = 'r'; /* 3 bits for user */
    if ( buf->st_mode & S_IWUSR ) str[2] = 'w';
    if ( buf->st_mode & S_IXUSR ) str[3] = 'x';
    if ( buf->st_mode & S_IRGRP ) str[4] = 'r'; /* 3 bits for group */
    if ( buf->st_mode & S_IWGRP ) str[5] = 'w';
    if ( buf->st_mode & S_IXGRP ) str[6] = 'x';
    if ( buf->st_mode & S_IROTH ) str[7] = 'r'; /* 3 bits for other */
    if ( buf->st_mode & S_IWOTH ) str[8] = 'w';
    if ( buf->st_mode & S_IXOTH ) str[9] = 'x';
    printf(str);
}
