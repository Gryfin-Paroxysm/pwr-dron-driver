#ifndef  PROSTOPADLOSCIAN_HH
#define  PROSTOPADLOSCIAN_HH

#include <string>

#include "punkt.hh"

struct prostopadloscian_struct{
    std::string _nazwa_przeszkody;
    punkt_struct _pozycja;
    punkt_struct _rozmiar;
};

#endif /// PROSTOPADLOSCIAN_HH
