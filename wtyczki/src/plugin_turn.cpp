#include "plugin_turn.hh"

/*!
 * \file
 * \brief Definicja klasy: C_turn
 *
 * Plik zawierający definicję klasy C_turn
 * która jest określana za pomocą klasy abstrakcyjnej C_plugin.
 */

/*!
 * wyświetla komende
 */
void C_turn::wyswietl_komende() const{
    std::cout << zwroc_nazwe_komendy()     << " "
              << _predkosc_drona_m_S       << " "
              << _dlugosc_drogi_m          << " "
              << _promien_krzywizny_luku_m << std::endl;
}

/*!
 * wyświetla składnie komendy
 */
void C_turn::wyswietl_skladnie_komendy() const{
    std::cout << "   Turn  predkosc_drona_m_S[mm/s]  dlugosc_drogi_m[mm]  promien_krzywizny_luku_m[mm]" << std::endl;
}

/*!
 * zwraca nazwę komendy
 */
const char* C_turn::zwroc_nazwe_komendy() const{
    return "Turn";
}

/*!
 * sprawdza poprawność parametrów
 */
bool C_turn::sprawdz_poprawnosc_parametrow() const{
    if(_promien_krzywizny_luku_m == 0){
        std::cerr << "promien zerowy" << std::endl;
        return false;
    }

    if( (_dlugosc_drogi_m == 0) && (_predkosc_drona_m_S != 0) ){
        std::cerr << "dystans zerowy ale prędkość nie zerowa" << std::endl;
        return false;
    }

    return true;
}

/*!
 * Wylicza współrzędne dla fragmentu przesunięcia
 */
void C_turn::oblicz_fragment(C_dron *dron) const{
    double promien = _promien_krzywizny_luku_m;
    bool promien_ujemny = false;
    if(promien<0){
        promien=-promien;
        promien_ujemny = true;
    }

    double predkosc = _predkosc_drona_m_S;
    bool predkosc_ujemna = false;
    if(_predkosc_drona_m_S < 0){
        predkosc = -predkosc;
        predkosc_ujemna = true;
    }

    double czas = abs(_dlugosc_drogi_m) / predkosc;
    double wycinek = abs(_dlugosc_drogi_m) / (_czestotliwosc*czas) ;

    while(wycinek >= 2*M_PI*promien)
        wycinek -= 2*M_PI*promien;

    double alpha = wycinek/promien;
    double d = 2*sin(alpha/2)*promien;

    punkt_struct p;
    if(!predkosc_ujemna){
        if(!promien_ujemny){
            p._x = cos(alpha/2)*d;
            p._y = sin(alpha/2)*d;
        }
        if(promien_ujemny){
            p._x = cos(-alpha/2)*d;
            p._y = sin(-alpha/2)*d;
        }
    }

    if(predkosc_ujemna){
        d = -d;
        if(!promien_ujemny){
            p._x = cos(-alpha/2)*d;
            p._y = sin(-alpha/2)*d;
        }
        if(promien_ujemny){
            p._x = cos(alpha/2)*d;
            p._y = sin(alpha/2)*d;
        }
    }

    double tmp_x = p._x;
    double tmp_y = p._y;
    double beta = dron->kat_w_stopniach()*(M_PI/180);
    p._x = cos(beta)*tmp_x - sin(beta)*tmp_y;
    p._y = sin(beta)*tmp_x + cos(beta)*tmp_y;

    beta  = beta *(180/M_PI);
    alpha = alpha*(180/M_PI);

    dron->ustaw_wspolrzedne(dron->wspolrzedne()._x + p._x, dron->wspolrzedne()._y + p._y,dron->wspolrzedne()._z);

    if(( (!predkosc_ujemna) && (!promien_ujemny) ) || ( ( predkosc_ujemna && promien_ujemny ) ))
        dron->ustaw_kat_w_stopniach(beta+alpha);
    else
        dron->ustaw_kat_w_stopniach(beta-alpha);
}

/*!
 * Wykonuje komende
 */
bool C_turn::wykonaj_komende(C_dron *dron) const{
    if(!this->sprawdz_poprawnosc_parametrow()){
        std::cerr << "Dane nie poprawne, komenda: ";
        wyswietl_komende();
        std::cerr << " jest wprowadzona ze złymi parametrami" << std::endl;
        return false;
    }

    if(_dlugosc_drogi_m == 0) return true;

    double czas = abs(_dlugosc_drogi_m) / abs(_predkosc_drona_m_S);
    for(int i=0;i<_czestotliwosc*czas;i++)
    {
        oblicz_fragment(dron);
        wyslij_informacje_do_wizualizacji(dron);
        usleep(_milisekundy/_czestotliwosc);
    }

    return true;
}

/*!
 * Wysyła informacje do wizualizacji
 */
void C_turn::wyslij_informacje_do_wizualizacji(C_dron *dron) const{
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
bool C_turn::odczytaj_komende(std::istream& strumien_komendy){
    strumien_komendy >> _predkosc_drona_m_S
                     >> _dlugosc_drogi_m
                     >> _promien_krzywizny_luku_m;
    if(strumien_komendy.fail())
        return false;
    return true;
}

/*!
 * zwraca instancję do klasy
 */
extern "C" C_plugin* stworz(){
    return new C_turn;
}

/*!
 * kasuje obiekt
 */
extern "C" void usun(C_plugin* objekt){
    delete objekt;
}
