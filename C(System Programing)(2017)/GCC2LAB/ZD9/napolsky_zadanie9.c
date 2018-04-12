#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
float a=0, b=0, c=0, d=0, e=0, f=0, g=0, h=0;
static int display_info(const char *fpath, const struct stat *sb,
             int tflag, struct FTW *ftwbuf)
{
   struct stat buf;
   lstat(fpath,&buf);
   if (S_ISREG(buf.st_mode)) a++; //"zwykly"
      else if (S_ISDIR(buf.st_mode)) b++; //"katalog"
      else if (S_ISCHR(buf.st_mode)) c++; //"specjalny znakowy"
      else if (S_ISBLK(buf.st_mode)) d++; //"specjalny blokowy"
      else if (S_ISFIFO(buf.st_mode)) e++; //"fifo"
   #ifdef S_ISLNK
   else if (S_ISLNK(buf.st_mode)) f++; //"dowiazanie"
   #endif
   #ifdef S_ISSOCK
   else if (S_ISSOCK(buf.st_mode)) g++; //"gniazdo"
   #endif
   else h++; //"UNKNOWN"
   return 0;
}
int main(int argc, char *argv[])
{
    if (nftw((argc < 2) ? "." : argv[1], display_info, 20, 0)==-1)
    {
        perror("nftw");
        exit(EXIT_FAILURE);
    }
    float sall=(a+b+c+d+e+f+g+h);
    printf("Mamy: %.0f plikow.\nProcentowy udzial:\nZwykle: %.1f%%\nKatalogi: %.1f%%\nSpecjalne znakowe: %.1f%%\nSpecjalne blokowe: %.1f%%\nFIFO: %.1f%%\nDowiazania: %.1f%%\nGniazda: %.1f%%\nNieznane: %.1f%%\n", sall, a/sall*100, b/sall*100, c/sall*100, d/sall*100, e/sall*100, f/sall*100, g/sall*100, h/sall*100);
    exit(EXIT_SUCCESS);
}
