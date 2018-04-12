#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>

void do_ls(char[]);
void do_lsl(char[]);
void show_stat_info(char*, char *);

int main(int argc, char *argv[]){
   int option;
   char optstring[] = ":l";
   if((option=getopt(argc,argv,optstring))==-1){
      if (argc==1)
            do_ls(".");
      else
         do_ls(*++argv);
   } else {
      switch (option){
         case 'l':
            if (argc==2){
               do_lsl(".");
            }
            else
               do_lsl(*(argv+2));
            break;
      }
   }
   return 0;
}

void do_ls(char dirname[]){
   DIR *dir_ptr;
   struct dirent *direntp;
   if ((dir_ptr=opendir(dirname))==NULL)
      fprintf(stderr,"ls1: cannot open %s\n", dirname);
   else{
   while ((direntp=readdir(dir_ptr))!=NULL)
      printf("%s\n", direntp->d_name);
   closedir(dir_ptr);
   }
}

void do_lsl(char dirname[]){
   DIR *dir_ptr;
   struct dirent *direntp;
   if ((dir_ptr=opendir(dirname))==NULL)
      fprintf(stderr,"ls1: cannot open %s\n", dirname);
   else{
   while ((direntp=readdir(dir_ptr))!=NULL){
      if(direntp->d_name[0]!='.'){
         char *str = NULL;
         asprintf(&str, "%s/%s", dirname, direntp->d_name);
         show_stat_info(str, direntp->d_name);
      }
   }
    closedir(dir_ptr);
  }
}

char* formatdate(char* str, time_t val){
   strftime(str, 36, "%b %e %H:%M", localtime(&val));
   return str;
}

void show_stat_info(char *fname, char *neim){
   struct stat info;
   stat(fname, &info);
   char mod[]="----------";
   if (S_ISDIR(info.st_mode)) mod[0] = 'd';
   if (S_ISCHR(info.st_mode)) mod[0] = 'c';
   if (S_ISBLK(info.st_mode)) mod[0] = 'b';
   if (info.st_mode & S_IRUSR) mod[1] = 'r';
   if (info.st_mode & S_IWUSR) mod[2] = 'w';
   if (info.st_mode & S_IXUSR) mod[3] = 'x';
   if (info.st_mode & S_IRGRP) mod[4] = 'r';
   if (info.st_mode & S_IWGRP) mod[5] = 'w';
   if (info.st_mode & S_IXGRP) mod[6] = 'x';
   if (info.st_mode & S_IROTH) mod[7] = 'r';
   if (info.st_mode & S_IWOTH) mod[8] = 'w';
   if (info.st_mode & S_IXOTH) mod[9] = 'x';
   struct group *grp;
   struct passwd *pwd;
   pwd = getpwuid(info.st_uid);
   grp = getgrgid(info.st_gid);
   char date[36];
   formatdate(date, info.st_mtime);
   printf("%s %d \t%s %s \t%lld \t%s %s\n", mod, info.st_nlink, pwd->pw_name, grp->gr_name, info.st_size, date, neim);
}
