#include "plugin_rotate.hh"

/*!
 * \file
 * \brief Definicja klasy: C_rotate
 *
 * Plik zawierający definicję klasy C_rotate
 * która jest określana za pomocą klasy abstrakcyjnej C_plugin.
 */

/*!
 * wyświetla komende
 */
void C_rotate::wyswietl_komende() const{
    cout << zwroc_nazwe_komendy() << " "
         << _predkosc_katowa_st_S      << " "
         << _kat_obrotu_st           << endl;
}

/*!
 * wyświetla składnie komendy
 */
void C_rotate::wyswietl_skladnie_komendy() const{
    cout << "   Rotate  predkosc_katowa_st_S[o/s]  predkosc_katowa_st_S[o] " << endl;
}

/*!
 * zwraca nazwę komendy
 */
const char* C_rotate::zwroc_nazwe_komendy() const{
    return "Rotate";
}

/*!
 * sprawdza poprawność parametrów
 */
bool C_rotate::sprawdz_poprawnosc_parametrow() const{
    if(_kat_obrotu_st < 0){
        std::cerr << "ujemny kąt obrotu" << std::endl;
        return false;
    }
    if(_predkosc_katowa_st_S == 0){
        std::cerr << "zerowa prędkość" << std::endl;
        return false;
    }

    return true;
}

/*!
 * Wylicza współrzędne dla fragmentu przesunięcia
 */
void C_rotate::oblicz_fragment(C_dron *dron) const{
    int czas = _kat_obrotu_st/abs(_predkosc_katowa_st_S);
    double odc_a;
    if(_predkosc_katowa_st_S < 0)
        odc_a = -(_kat_obrotu_st/((double)_czestotliwosc*czas));
    else
        odc_a =   _kat_obrotu_st/((double)_czestotliwosc*czas);

    dron->ustaw_kat_w_stopniach(dron->kat_w_stopniach() + odc_a);
}

/*!
 * Wykonuje komende
 */
bool C_rotate::wykonaj_komende(C_dron *dron) const{
    if(!this->sprawdz_poprawnosc_parametrow()){
        std::cerr << "Dane nie poprawne, komenda: ";
        wyswietl_komende();
        std::cerr << " jest wprowadzona ze złymi parametrami" << std::endl;
        return false;
    }

    if(_kat_obrotu_st == 0) return true;

    int czas = _kat_obrotu_st/abs(_predkosc_katowa_st_S);
    for(int i=0;i<_czestotliwosc*czas;i++){
        oblicz_fragment(dron);
        wyslij_informacje_do_wizualizacji(dron);
        usleep(_milisekundy/_czestotliwosc);
    }

    return true;
}

/*!
 * Wysyła informacje do wizualizacji
 */
void C_rotate::wyslij_informacje_do_wizualizacji(C_dron *dron) const{
    std::stringstream strumien_informacji;
    strumien_informacji << 's' << ';';
    strumien_informacji << dron->wspolrzedne()._x << ';';
    strumien_informacji << dron->wspolrzedne()._z << ';';
    strumien_informacji << dron->wspolrzedne()._y << ';';
    strumien_informacji << -dron->kat_w_stopniach();
    std::string informacja = strumien_informacji.str();
    dron->przekaz_informacje_do_pamieci(informacja);
}

/*!
 * Odczytuje komende
 */
bool C_rotate::odczytaj_komende(std::istream& strumien_komendy){
    strumien_komendy >> _predkosc_katowa_st_S
                     >> _kat_obrotu_st;
    if(strumien_komendy.fail())
        return false;
    return true;
}

/*!
 * zwraca instancję do klasy
 */
extern "C" C_plugin* stworz(){
    return new C_rotate;
}

/*!
 * kasuje obiekt
 */
extern "C" void usun(C_plugin* objekt){
    delete objekt;
}
