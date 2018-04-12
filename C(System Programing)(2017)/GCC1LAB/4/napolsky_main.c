#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/utsname.h>

int main(int argc, char *argv[]) {
        char *login;
        struct utsname utsname;
        struct passwd *opis;

        int opcja;
        int kod_powrotu=0;
        char optstring[] = "u::s"; /* rozpoznawane opcje */
        while ( (opcja = getopt(argc,argv,optstring)) != -1 )
                switch ( opcja ) {
                case 'u':

/* Pobierz nazwe wlasciciela procesu*/
                        if((login = getlogin()) == NULL) {
                                perror("getlogin");
                                exit(EXIT_FAILURE);
                        }

/* Jezeli byl podany argument opcji */
// if(argc==3){
//     login=argv[2];
// }
                        login=optarg;

/* Odszukaj opis w /etc/passwd */
                        if((opis= getpwnam(login)) == NULL) {
                                perror("getpwnam");
                                exit(EXIT_FAILURE);
                        }

/* Wyswietl informacje o uzytkowniku */
                        printf("user name: %s\n", opis->pw_name);
                        printf("UID : %d\n", opis->pw_uid);
                        printf("GID : %d\n", opis->pw_gid);
                        printf("gecos : %s\n", opis->pw_gecos);
                        printf("home dir : %s\n", opis->pw_dir);
                        printf("shell : %s\n", opis->pw_shell);

                        break;

                case 's':

/* Wyswietl informacje o systemie */

                        if (uname (&utsname) != -1) {
                                printf ("\nInfo from uname:\n");
                                printf (" sysname: %s\n", utsname.sysname);
                                printf (" nodename: %s\n", utsname.nodename);
                                printf (" release: %s\n", utsname.release);
                                printf (" version: %s\n", utsname.version);
                                printf (" machine: %s\n\n", utsname.machine);
                        }

                        break;
//case '?' :
                default:
                        fprintf(stderr, "opcja -%c nie znana – ignoruje\n", optopt);
                        kod_powrotu = 1; /* Wystapil blad */
                        break;
                }

        return kod_powrotu;

        exit(EXIT_SUCCESS);
}
