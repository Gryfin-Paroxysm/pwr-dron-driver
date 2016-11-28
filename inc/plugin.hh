#ifndef PLUGIN_HH
#define PLUGIN_HH

/*!
 * \file
 * \brief Klasa: C_plugin
 *
 * Plik zawierający definicję klasy abstrakcyjnej dla wtyczek.
 * Klasa bazowa każdej wtyczki.
 *
 * Zadaniem głównym tej klasy jest:
 * - zdefiniowanie koncepcji budowy wtyczki (interpreter wtyczek)
 * - wprowadzenie metod wirtualnych
 */

#include "dron.hh"
#include "scena.hh"

#include <iostream>
using namespace std;

/*!
 * \brief wprowadzamy model abstrakcyjnej klasy pluginu
 *
 *  Klasa zawiera tylko pustę pola wirtualne.
 */
class C_plugin {

  public:

    /*!
     * \brief destruktor wirtualny
     *
     *  Umożliwia poprawne usuwanie obiektów z pamięci. Jego obecność jest zalecana
     *  Przez twórców biblioteki dlfcn.
     */
   virtual ~C_plugin() {}

   /*!
     * \brief Wirtualna metoda wprowadzająca możliwość wyświetlenia komendy
     *
     *  Metoda powinna wyświetlić nazwę komendy wtyczki
     */
   virtual void wyswietl_komende() const = 0;

   /*!
     * \brief Wirtualna metoda wprowadzająca możliwość wyświetlenia składni komendy
     *
     *  Metoda poeinna wyświetlić całą składnię komendy danej wtyczki
     */
   virtual void wyswietl_skladnie_komendy() const = 0;

   /*!
     * \brief Wirtualna metoda wprowadzająca zwracanie nazwy komendy
     *
     *  Metoda powinna zwrócić nazwę komendy, którą wykonuje dana wtyczka
     *   \retval napis - nazwa komendy
     */
   virtual const char* zwroc_nazwe_komendy() const = 0;

   /*!
     * \brief Wirtualna metoda wprowadzająca możliwość wykonania komendy
     *
     *  Metoda powinna realizować główne zadanie przewidziane dla komendy
     *   \retval prawda - jeśli komenda została poprawnie wykonana
     */
   virtual bool wykonaj_komende(C_dron *dron) const = 0;

   /*!
     * \brief Wirtualna metoda wprowadzająca możliwość odczytania komendy
     *  \param[in] strumień - wejście dla danych, ich sekwencje określa metoda wyświetlająca składnie
     *
     *  Metoda powinna przetworzyć dane wejściowe i zainicjalizować obiekt swojej klasy
     *   \retval prawda - jeśli udało się poprawnie odczytać informacje wejściowe
     */
   virtual bool odczytaj_komende(std::istream& strumien_komendy) = 0;

};

#endif /// PLUGIN_HH
