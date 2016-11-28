#ifndef PAUSE_HH
#define PAUSE_HH

#include "plugin.hh"

#include <iostream>
#include <cmath>
#include <unistd.h>


class C_pause: public C_plugin {

	unsigned _czas_w_ms;

  public:

    virtual void wyswietl_komende() const;
    virtual void wyswietl_skladnie_komendy() const;
    virtual const char* zwroc_nazwe_komendy() const;
    virtual bool wykonaj_komende(C_dron *dron) const;
    virtual bool odczytaj_komende(std::istream& strumien_komendy);

    static C_plugin* stworz();
    static void usun(C_plugin* objekt);

};

#endif /// PAUSE_HH

