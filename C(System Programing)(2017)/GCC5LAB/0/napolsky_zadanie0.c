/*
 * Zadanie 8. Demony
 * a) Napisz program, który będzie działał jako demon.
 * Zadaniem programu jest wpisywanie znacznika czasu do pliku co jedną minutę.
 * Program ma przesyłać komunikat o uruchomieniu i ewentualnych błędach do demona syslogd.
 * Wskazówka: użyj funkcji bibliotecznej daemon() .
 *
 * b) Uzupełnij program o czytanie pliku konfiguracyjnego, w którym podawana jest częstotliwość
 * generowania znacznika czasu.
 *
 * c) Zmodyfikuj program tak, aby w trakcie działania programu możliwe było ponowne przeczytanie
 * pliku konfiguracyjnego. Wskazówka: wykorzystaj sygnał SIGHUP.
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <syslog.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FILENAME "zad8.conf"

sig_atomic_t seconds = 60;

int get_current_timestamp() {
    time_t current;
    return time(&current);
} //pobieramy czas

void formatdate(char* str, time_t val) {
    strftime(str, 36, "%d.%m.%Y %H:%M:%S\n", localtime(&val));
} //time_t to *char

int file_exists(char * filename) {
    return access(filename, F_OK) != -1;
} //czy file istnieje

void append_file_content(char * filename, char * cnt) {
    FILE *fp;
    if ((fp = fopen(filename, "a+")) == NULL) {
        fprintf(stderr, "Can't open file: %s\n", filename);
        syslog(LOG_ERR, "Can't open file: %s\n", filename);

        exit(1);
    }
    fputs(cnt, fp);
    fclose (fp);
} //dodaj aktualny czas do pliku

void save_time_to_file() {
    char str[40];
    formatdate(str, get_current_timestamp()); 
    append_file_content("test_file.dat", str);
} //zapisz biezacy czas do pliku test_file.dat

int load_configuration_time(char * filename) {
    FILE * fd;
    int time = -1;

    if (!file_exists(filename)) {
        fprintf(stderr, "File not exists: %s\n", filename);
        syslog(LOG_ERR, "File not exists: %s\n", filename);
    }
    if ((fd = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Can't open file: %s\n", filename);
        syslog(LOG_ERR, "Can't open file: %s\n", filename);
    }
    if (fscanf(fd, "%d\n", &time) == EOF) {
        fprintf(stderr, "Can't scan file: %s\n", filename);
        syslog(LOG_ERR, "Can't scan file: %s\n", filename);
    }
    fclose(fd);

    return time;
} //pobierz czasowy znacznik

void sig_hup_handler() {
    int time = load_configuration_time(FILENAME);
    seconds=time;
} //odswiezenie interwalu

int daemon_start() {
    int i;
    pid_t pid;
    /* Utwórz nowy proces */
    pid=fork();
    if (pid == -1) return -1;
    else if (pid !=0) exit(EXIT_SUCCESS); /*proces macierzysty kończy działanie */
    /* Utwórz nową sesję i grupę procesów */
    if (setsid() == -1) return -1;
    /* Zmiana katalogu roboczego */
    if (chdir("/") == -1) return -1;
    /* Zerowanie maski tworzenia pliku */
    umask(0);
    /* Zamknięcie wszystkich otwartych plików */
    for (i=getdtablesize()-1; i>=0; --i) close(i);
    /* Przekierowanie 0,1,2 do /dev/null */
    open("/dev/null",O_RDWR); /* stdin */
    dup(0); /* stdout */
    dup(0); /* stderr */
    return 0;
} //demon

int main(int argc, char * argv[]) {
    /* 1) pobieramy z konfiguracji time */
    seconds = load_configuration_time(FILENAME);

    /* 2) odświeżamy czas w przypadku odpowiedniego sygnału */
    signal(SIGHUP, sig_hup_handler);

    /* 3) uruchamiamy demona */
    daemon(1, 1);
    //daemon_start();
    
    /* 4) informujemy syslogd o uruchomieniu */
    openlog(argv[0], LOG_PID, 0);

    /* 5) zapisujemy do pliku co jedną minutę aktualny timestamp */
    for(;;){
        sleep(seconds);
        save_time_to_file();
    }
    return 0;
}
