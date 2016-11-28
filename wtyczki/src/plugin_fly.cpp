#include "plugin_fly.hh"

/*!
 * \file
 * \brief Definicja klasy: C_fly
 *
 * Plik zawierający definicję klasy C_fly
 * która jest określana za pomocą klasy abstrakcyjnej C_plugin.
 */

/*!
 * wyświetla komende
 */
void C_fly::wyswietl_komende() const {
    std::cout << zwroc_nazwe_komendy()      << " "
              << _predkosc_horyzontalna_m_S << " "
              << _predkosc_wertykalna_m_S   << " "
              << _droga_m                   << " "
              << std::endl;
}

/*!
 * wyświetla składnie komendy
 */
void C_fly::wyswietl_skladnie_komendy() const{
    std::cout << "   Fly  predkosc_horyzontalna_m_S[m/s]  predkosc_wertykalna_m_S[m/s]  droga_m[m]" << std::endl;
}

/*!
 * zwraca nazwę komendy
 */
const char* C_fly::zwroc_nazwe_komendy() const{
    return "Fly";
}

/*!
 * sprawdza poprawność parametrów
 */
bool C_fly::sprawdz_poprawnosc_parametrow() const{
    if(_droga_m == 0)
        if( (_predkosc_wertykalna_m_S != 0) || (_predkosc_horyzontalna_m_S !=0 ) ){
            std::cerr << "prędkości nie zerowe, gdy droga zerowa" << std::endl;
            return false;
        }

    if(_droga_m < 0){
       std::cerr << "droga ujemna" << std::endl;
       return false;
    }

    if(_droga_m > 0)
        if( (_predkosc_wertykalna_m_S == 0) && (_predkosc_horyzontalna_m_S == 0) ){
            std::cerr << "prędkości zerowe, gdy droga nie zerowa" << std::endl;
            return false;
        }

    return true;
}

/*!
 * Wylicza współrzędne dla fragmentu przesunięcia
 */
void C_fly::oblicz_fragment(C_dron *dron) const{
    punkt_struct p;
    if(_predkosc_horyzontalna_m_S == 0){
        if(_predkosc_wertykalna_m_S > 0)
            p._z = _droga_m;
        else
            p._z =-_droga_m;
    }
    else if(_predkosc_wertykalna_m_S == 0){
        if(_predkosc_horyzontalna_m_S > 0)
            p._x = _droga_m;
        else
            p._x = -_droga_m;
    }
    else{
        double alpha = atan(abs(_predkosc_wertykalna_m_S)/abs(_predkosc_horyzontalna_m_S));
        (_predkosc_wertykalna_m_S   < 0) ? (p._z = -_droga_m * sin(alpha) ) : (p._z = _droga_m*sin(alpha));
        (_predkosc_horyzontalna_m_S < 0) ? (p._x = -_droga_m * cos(alpha) ) : (p._x = _droga_m*cos(alpha));
    }

    double tmp_x = p._x;
    double tmp_y = p._y;
    double beta = dron->kat_w_stopniach()*(M_PI/180);

    p._x = tmp_x*cos(beta) - tmp_y*sin(beta);
    p._y = tmp_y*cos(beta) + tmp_x*sin(beta);

    int czas= _droga_m/(abs(_predkosc_horyzontalna_m_S)+abs(_predkosc_wertykalna_m_S));

    double x_odc = p._x / ((double)_czestotliwosc*czas);
    double y_odc = p._y / ((double)_czestotliwosc*czas);
    double z_odc = p._z / ((double)_czestotliwosc*czas);

    dron->ustaw_wspolrzedne(dron->wspolrzedne()._x + x_odc,dron->wspolrzedne()._y + y_odc,dron->wspolrzedne()._z + z_odc);
}

/*!
 * Wykonuje komende
 */
bool C_fly::wykonaj_komende(C_dron *dron) const{
    if(!this->sprawdz_poprawnosc_parametrow()){
        std::cerr << "Dane nie poprawne, komenda: ";
        wyswietl_komende();
        std::cerr << " jest wprowadzona ze złymi parametrami" << std::endl;
        return false;
    }

    if(_droga_m == 0) return true;

    int czas= _droga_m/(abs(_predkosc_horyzontalna_m_S)+abs(_predkosc_wertykalna_m_S));
    for(int i=0;i<(_czestotliwosc*czas);i++){
        oblicz_fragment(dron);
        wyslij_informacje_do_wizualizacji(dron);
        usleep(_milisekundy/_czestotliwosc);
    }

    return true;
}

/*!
 * Wysyła informacje do wizualizacji
 */
void C_fly::wyslij_informacje_do_wizualizacji(C_dron *dron) const{
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
bool C_fly::odczytaj_komende(std::istream& strumien_komendy){
    strumien_komendy >> _predkosc_horyzontalna_m_S
                     >> _predkosc_wertykalna_m_S
                     >> _droga_m;
    if(strumien_komendy.fail())
        return false;
    return true;
}

/*!
 * zwraca instancję do klasy
 */
extern "C" C_plugin* stworz(){
    return new C_fly;
}

/*!
 * kasuje obiekt
 */
extern "C" void usun(C_plugin* objekt){
    delete objekt;
}
