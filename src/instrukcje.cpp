#include "instrukcje.hh"

/*!
 * \file
 * \brief Definicja klasy: C_instrukcje
 *
 * Plik zawierający definicję klasy C_instrukcje,
 * która jest wykorzystywana przez wtyczki do kontorli obiektem.
 */

/*!
* Zwraca rozmiar wektora _sekwencje_instrukcji
*/
unsigned C_instrukcje::pobierz_rozmiar_sekwencji_instrukcji(){
    return _sekwencje_instrukcji.size();
}

/*!
* Zwraca wartość wektora w polu i
*/
std::string C_instrukcje::pobierz_sekwencje_instrukcji(unsigned i){
    return _sekwencje_instrukcji[i];
}

/*!
* Pobiera nazwę od użytkownika, wczytuje plik, przetważa go preprocesorem.
* Pobiera informacje z pliku do wektora.
*/
void C_instrukcje::wczytanie_nazwy_pliku_sekwencji_instrukcji_dla_drona(std::string nazwa_pliku){
    _sekwencje_instrukcji.clear();

    if(nazwa_pliku == ""){
        std::cout << "Podaj nazwe pliku: ";
        std::cin >> nazwa_pliku;
    }

    FILE* uchwyt_pliku_preprocesora = popen(std::string("cpp -P " + nazwa_pliku).c_str(),"r");
    if(!uchwyt_pliku_preprocesora){
        std::cerr << "Błąd odczytu pliku" << std::endl;
        return;
    }

    __gnu_cxx::stdio_filebuf<char> powiazanie_posix_ze_strumieniem_pliku(uchwyt_pliku_preprocesora, std::ios_base::in);
    std::iostream strumien_pliku(&powiazanie_posix_ze_strumieniem_pliku);

    std::fstream plik;
    plik.std::ios::rdbuf(strumien_pliku.rdbuf());
    while(!plik.eof()){
        std::string komenda;
        getline(plik,komenda);
        if(komenda != "")
            _sekwencje_instrukcji.push_back(komenda);
    }
    plik.close();
    pclose(uchwyt_pliku_preprocesora);
}

/*!
* Wyświetla zawartość wektora _sekwencje_instrukcji
*/
void C_instrukcje::pokaz_sekwencje_instrukcji(){
    for(unsigned i=0;i<_sekwencje_instrukcji.size();i++){
        std::cout << _sekwencje_instrukcji[i] << std::endl;
    }
}
