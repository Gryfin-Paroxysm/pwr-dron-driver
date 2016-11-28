#ifndef  WTYCZKA_LOADER_HH
#define  WTYCZKA_LOADER_HH

/*!
 * \file
 * \brief Struktura: wtyczka_loader_struct
 *
 * Plik zawierający definicję struktury wtyczka_loader_struct,
 * która jest wykorzystywana do bezpośredniej komunikacji z bibiliotekami
 * dynamicznymi, wykorzystywana przez klasę C_wtyczki.
 *
 * Zadaniem głównym tej struktury jest:
 * - zdeklarowanie pola wskaźnika do pluginu
 * - zdeklarowanie pola wskaźnika do uchwytu na ten plugin
 * - zdeklarowanie pola do wskaźnika tworzącego i usuwającego plugin
 */

#include "plugin.hh"

/*!
 * \brief struktura zbioru wskaźników do wtyczek
 *
 *  Struktura zawiera niezbędnę do poprawnego działania i całościowej obsługi
 *  wskaźniki odnoszące się do pluginu.
 */
struct wtyczka_loader_struct{
    C_plugin* _wskaznik_do_pluginu;
    void* _uchwyt_do_pluginu;
    C_plugin* (*_stworz_plugin)(void);
    void (*_usun_plugin)(C_plugin*);
};

#endif /// WTYCZKA_LOADER_HH
