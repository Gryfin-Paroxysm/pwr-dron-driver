#include "pamiec_wspoldzielona.hh"

void inicjalizacja_pamieci_wspolnej(int shared_size, struct shared_struct **shared_mem){
    XInitThreads();

    shm_unlink(SHM_TESTMEM);
    int shmd = shm_open(SHM_TESTMEM, O_RDWR|O_CREAT, MODES);
    shared_size = sizeof(struct shared_struct);
    ftruncate(shmd, shared_size);
    *shared_mem = (struct shared_struct *) mmap(NULL,shared_size,PROT_READ|PROT_WRITE,MAP_SHARED,shmd,0);
    (*shared_mem)->client_wrote = 0;
}

void deinicjalizacja_pamieci_wspolnej(int shared_size, struct shared_struct **shared_mem){
    munmap((char *)*shared_mem, shared_size);
}
