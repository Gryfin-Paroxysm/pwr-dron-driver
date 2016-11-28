#ifndef TURN_HH
#define TURN_HH

/*!
 * \file
 * \brief Klasa wtyczka: C_turn
 *
 * Plik zawierający definicję nagłówka klasy wtyczka C_turn,
 * która jest określana za pomocą klasy abstrakcyjnej C_plugin
 *
 * Zadaniem głównym tej klasy jest:
 * - Zrealizowanie obliczeń dla zadania turn
 * - obsługa funkcjonalności wtyczki
 * - udostępnienie w języku C metod dostępowych do biblioteki
 */

#include "plugin.hh"

#include <iostream>
#include <cmath>
#include <unistd.h>

/*!
 * \brief wprowadzamy model klasy wtyczki C_turn
 *
 *  Klasa pozwalająca na realizację zadania turn
 */
class C_turn: public C_plugin {

/*!
 * \brief częstotliowść
 *
 * Ustawienia częstotliwości odświerzania dla programu graficznego
 */
    int _czestotliwosc = 10;

/*!
 * \brief milisekundy
 *
 * czas dla animacji obiektu w programie graficznym
 */
    int _milisekundy = 1000000;

/*!
 * \brief prędkość drona
 *
 * Prędkość drona wyrażona w metrach na sekundę
 */
    double _predkosc_drona_m_S = 0;

/*!
 * \brief długośc drogi
 *
 * Długośc drogi wyrażona w metrach
 */
    double _dlugosc_drogi_m = 0;

/*!
 * \brief promień krzywizny łuku
 *
 * Promień krzywizny łuku wyrażony w metrach
 */
    double _promien_krzywizny_luku_m = 0;

  public:

    /*!
     * \brief Metoda wyświetlająca komendę
     *
     *  Wyświetla komende
     */
    virtual void wyswietl_komende() const;

    /*!
     * \brief Metoda wyświetlająca składnie komendy
     *
     *  Wyświetla składnie komendy
     */
    virtual void wyswietl_skladnie_komendy() const;

    /*!
     * \brief Metoda zwracająca nazwę komendy
     *
     *  Zwraca nazwę komendy
     *  \retval nazwa komendy
     */
    virtual const char* zwroc_nazwe_komendy() const;

    /*!
     * \brief Metoda wykonująca komendę
     *  \param[in] obiekt dron
     *
     *  Wykonuje obliczenia dla danej komendy
     *  \retval prawda - jeśli udało się wykonać komende
     */
    virtual bool wykonaj_komende(C_dron *dron) const;

    /*!
     * \brief Metoda odczytująca parametry dla komendy
     *  \param[in] strumień wejściwy - powinien zawierać dane dla komendy
     *
     *  Wczytuje komende z strumienia wejściowego
     *  \retval prawda - jeślu udało się poprawnie wczytać wartości
     */
    virtual bool odczytaj_komende(std::istream& strumien_komendy);

    /*!
     * \brief Metoda statyczna zwracająca instancję do klasy C_rotate
     *
     *  Zwraca instancję do klasy C_rotate
     *  \retval obiekt klasy C_rotate
     */
    static C_plugin* stworz();

    /*!
     * \brief Metoda statyczna usuwająca obiekt z pamięci
     *  \param[in] obiekt klasy C_rotate
     *
     *  Czyści pamięć - usuwa obiekt C_rotate
     */
    static void usun(C_plugin* objekt);

  private:

    /*!
     * \brief Prywatna metoda sprawdzająca poprawność danych wejściowych
     *
     *  Sprawdza poprawność parametrów
     *  \retval prawda - jeśli wczytane parametry są prawidłowe
     */
    bool sprawdz_poprawnosc_parametrow() const;

    /*!
     * \brief Prywatna metoda pozwalająca na komunikację z przez pamięć współdzieloną
     *  \param[in] obiekt klasy C_dron
     *
     *  Wysyła informacje do wizualizacji
     */
    void wyslij_informacje_do_wizualizacji(C_dron *dron) const;

    /*!
     * \brief Prywatna metoda realizująca obliczenia
     *  \param[in] obiekt klasy C_dron
     *
     *  Oblicza fragmentrycznie przesunięcie obiektu drona
     */
    void oblicz_fragment(C_dron *dron) const;

};

#endif /// TURN_HH

