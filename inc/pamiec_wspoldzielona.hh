#ifndef  PAMIEC_WSPOLDZIELONA_HH
#define  PAMIEC_WSPOLDZIELONA_HH

#include <X11/Xlib.h>
#include <cstdio>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>

#define POSIX_SOURCE
#define SHM_TESTMEM "/shm_testmem"
#define MODES 0666

struct shared_struct {
    int client_wrote;
    char text[BUFSIZ];
};

void inicjalizacja_pamieci_wspolnej(int shared_size, struct shared_struct **shared_mem);
void deinicjalizacja_pamieci_wspolnej(int shared_size, struct shared_struct **shared_mem);

#endif /// PAMIEC_WSPOLDZIELONA_HH
