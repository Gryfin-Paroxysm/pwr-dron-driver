#include "wtyczki.hh"

/*!
 * \file
 * \brief Definicja klasy: C_wtyczki
 *
 * Plik zawierający definicję klasy C_wtyczki,
 * która jest dziedziczona przez klasę C_klasa_glowna.
 * Zapewniając możliwość interakcji z bibliotekami dynamicznymi
 */

/*!
 * Zwraca wskaźnik do drugiego pola w mapie, daje dostęp do metod wtyczki
 */
wtyczka_loader_struct* C_wtyczki::odnosnik_do_wczytanego_pluginu(std::string nazwa_instrukcji){
    return _wczytane_pluginy.find(nazwa_instrukcji)->second;
}

/*!
 * Wyświetlanie dostępnych wtyczek
 */
void C_wtyczki::pokaz_dostepne_wtyczki(){
    std::cout << "Dostępne pluginy: " << std::endl;
    for(_it=_wczytane_pluginy.begin();_it!=_wczytane_pluginy.end();++_it)
        std::cout << _it->first << std::endl;
}

/*!
 * Dodanie nowej wtyczki, pobiera nazwę
 * sprawdza czy załadowana
 * inicjalizuje pamięć i łączy wskaźnikami
 * uzupełnia mape
 */
void C_wtyczki::dodaj_nowa_wtyczke(std::string nazwa_pluginu){
    if(nazwa_pluginu == ""){
        std::cout << " Podaj nazwe pluginu: ";
        std::cin >> nazwa_pluginu;
    }

    if(sprawdz_czy_zaladowana(nazwa_pluginu)){
        std::cerr << "Ta biblioteka jest już załadowana" << endl;
        return;
    }

    wtyczka_loader_struct* nowy_plugin;
    nowy_plugin = new wtyczka_loader_struct;

    std::string sciezka_do_biblioteki = nazwa_pluginu + ".so";
    nowy_plugin->_uchwyt_do_pluginu = dlopen(sciezka_do_biblioteki.c_str(), RTLD_LAZY);
    if (!nowy_plugin->_uchwyt_do_pluginu){
        std::cerr << "Nie można odnaleźć biblioteki: " << dlerror() << std::endl;
        return;
    }

    nowy_plugin->_stworz_plugin = (C_plugin* (*)()) dlsym(nowy_plugin->_uchwyt_do_pluginu, "stworz");
    if(blad_dlfcn("Nie można odnaleźć podanego symbolu w bibliotece "))
        return;

    nowy_plugin->_usun_plugin = (void (*)(C_plugin*)) dlsym(nowy_plugin->_uchwyt_do_pluginu, "usun");
    if(blad_dlfcn("Nie można odnaleźć podanego symbolu w bibliotece "))
        return;

    _wczytane_pluginy[nazwa_pluginu] = nowy_plugin;

    _wczytane_pluginy.find(nazwa_pluginu)->second->_wskaznik_do_pluginu = _wczytane_pluginy.find(nazwa_pluginu)->second->_stworz_plugin();

    std::cout << "plugin: " << nazwa_pluginu << ".so dodany" << std::endl;
}

/*!
 * Usuwa wtyczkę
 */
void C_wtyczki::usun_wtyczke(){
    std::string nazwa_pluginu;
    std::cout << " Podaj nazwe pluginu: ";
    std::cin >> nazwa_pluginu;

    if(!sprawdz_czy_zaladowana(nazwa_pluginu)){
        std::cerr << "Podana biblioteka nie została załadowana" << std::endl;
        return;
    }

    _wczytane_pluginy.find(nazwa_pluginu)->second->_usun_plugin(_wczytane_pluginy.find(nazwa_pluginu)->second->_wskaznik_do_pluginu);

    dlclose(_wczytane_pluginy.find(nazwa_pluginu)->second->_uchwyt_do_pluginu);
    _it = _wczytane_pluginy.find(nazwa_pluginu);
    if (_it != _wczytane_pluginy.end())
        _wczytane_pluginy.erase(_it);

    std::cout << "plugin usuniety" << std::endl;
}

/*!
 * Sprawdza czy wtyczka została wcześniej załadowana do mapy
 */
bool C_wtyczki::sprawdz_czy_zaladowana(std::string nazwa_pluginu){
    for(_it=_wczytane_pluginy.begin();_it!=_wczytane_pluginy.end();++_it)
        if(_it->first == nazwa_pluginu)
            return true;
    return false;
}

/*!
 * Asercja dla obsługi biblioteki dlfcn
 */
bool C_wtyczki::blad_dlfcn(const char* napis){
    const char* dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << napis << dlsym_error << std::endl;
        return true;
    }
    return false;
}
