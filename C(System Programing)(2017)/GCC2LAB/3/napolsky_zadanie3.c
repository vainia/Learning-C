#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    struct stat info;
    if (argc>1) {
      if( stat(argv[1], &info) != -1 ){
                switch(*argv[2]){
                    case 'r':
                        if ( info.st_mode & S_IRUSR ) printf("USER MOZE\n"); /* 3 bits for user */
                        if ( info.st_mode & S_IRGRP ) printf("GROUP MOZE\n"); /* 3 bits for group */
                        if ( info.st_mode & S_IROTH ) printf("OTHER MOZE\n"); /* 3 bits for other */
                            return 0;
                        break;
                    case 'w':
                        if ( info.st_mode & S_IWUSR ) printf("USER MOZE\n"); /* 3 bits for user */
                        if ( info.st_mode & S_IWGRP ) printf("GROUP MOZE\n"); /* 3 bits for group */
                        if ( info.st_mode & S_IWOTH ) printf("OTHER MOZE\n"); /* 3 bits for other */
                        break;
                    case 'x':
                        if ( info.st_mode & S_IXUSR ) printf("USER MOZE\n"); /* 3 bits for user */
                        if ( info.st_mode & S_IXGRP ) printf("GROUP MOZE\n"); /* 3 bits for group */
                        if ( info.st_mode & S_IXOTH ) printf("OTHER MOZE\n"); /* 3 bits for other */
                        break;
                    default:
                        printf("Podano niewlasciwy parametr");
                        break;
                }
            return 0;
      }
      else
          printf("Plik nie istnieje\n");
    }
    else
      printf("Uzycie: %s nazwa_pliku\n",argv[0]);
    return 1;
}
