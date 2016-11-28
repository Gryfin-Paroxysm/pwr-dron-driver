#include "dron.hh"

/*!
 * \file
 * \brief Definicja klasy: C_dron
 *
 * Plik zawierający definicję klasy C_dron
 * która jest wykorzystywana przez wtyczki do kontorli obiektem.
 * Zapewniając funkcjonalność sterowania dronem i przechowywania w nim informacji.
 */

/*!
 * Pozwala ustawić współrzędne za pomocą x,y,z
 */
void C_dron::ustaw_wspolrzedne(double x, double y, double z){
    _wspolrzedne._x = x;
    _wspolrzedne._y = y;
    _wspolrzedne._z = z;
}

/*!
 * Ustawia współrzędne za pomocą punktu
 */
void C_dron::ustaw_wspolrzedne(const punkt_struct&  wspolrzedne){
    _wspolrzedne = wspolrzedne;
}

/*!
 * Ustawia kąt (w stopniach)
 */
void C_dron::ustaw_kat_w_stopniach(double kat_w_stopniach){
    _kat_w_stopniach = kat_w_stopniach;
}

/*!
 * Zwraca współrzędne za pomocą punktu
 */
punkt_struct C_dron::wspolrzedne() const{
    return _wspolrzedne;
}

/*!
 * Zwraca kąt (w stopniach)
 */
double C_dron::kat_w_stopniach() const{
    return _kat_w_stopniach;
}

/*!
 * Zapisuje pozycje do strumienia pliku
 */
void C_dron::zapisz_pozycje_w_pliku(std::fstream& plik){
    plik << _wspolrzedne._x << " "
         << _wspolrzedne._y << " "
         << _wspolrzedne._z << " "
         << _kat_w_stopniach << std::endl;
}

/*!
 * Wyświetla pozycję na standardowym wyjściu
 */
void C_dron::wyswietl_pozycje(){
    std::cout << _wspolrzedne._x << " "
              << _wspolrzedne._y << " "
              << _wspolrzedne._z << " "
              << _kat_w_stopniach << std::endl;
}

/*!
 * łączy pamięć współdzieloną
 */
void C_dron::polacz_komunikacje(struct shared_struct *lacznik_shared_mem){
    global_shared_mem = lacznik_shared_mem;
}

/*!
 * Przekazuje informacje do pamięci współdzielonej
 */
void C_dron::przekaz_informacje_do_pamieci(std::string napis){
    while(global_shared_mem->client_wrote == 1) {}
    strcpy(global_shared_mem->text, napis.c_str());
    global_shared_mem->client_wrote = 1;
}
