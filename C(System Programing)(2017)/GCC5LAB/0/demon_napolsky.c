#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <syslog.h>

/*!
 * @param pname - wskaźnik do nazwy procesu
 * @param facility - klasa usług dla syslogd
 */
int daemon_start(const char * pname, int facility) {
    int i;
    pid_t pid = fork();

    // utworzenie potomka
    if (pid < 0) {
        // problem
        printf("ERR: problem ze stworzeniem procesu\n");
        return -1;
    }

    if (pid) {
        // macierzysty
        exit(EXIT_SUCCESS);
    }

    // potomek wykonuje dalszą pracę

    /*******************************************************/

    // tworzymy nową grupę procesów - nowy przywódca sesji
    // nie ma przypisanego terminala sterującego
    if (setsid() == -1) {
        // problem
        return -1;
    }

    /*******************************************************/

    // zmiana bieżącego katalogu na katalog główny
    if (chdir ("/") == -1) {
        // problem
        return -1;
    }

    /*******************************************************/

    // zmiana maski dostępu
    umask(0);

    /*******************************************************/

    // zamykamy wszystkie otwarte deskryptory
    for (i = 0; i < getdtablesize(); i++) close(i);

    /*******************************************************/

    // otwiramy 3 std. strumienie na /dev/null
    open("/dev/null", O_RDWR); // stdin
    dup(0); // stdout
    dup(0); // stderr

    /*******************************************************/

    // rejestracja komunikatów do syslogd
    openlog(pname, LOG_PID, facility);

    return 0;
} 
