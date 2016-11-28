#ifndef  INSTRUKCJE_HH
#define  INSTRUKCJE_HH

/*!
 * \file
 * \brief Klasa: C_instrukcje
 *
 * Plik zawierający definicję nagłówka klasy C_instrukcje,
 * która jest dziedziczona przez klasę C_klasa_glowna.
 * Zapewniając jej dodatkową funkcjonalność w zakresie
 * przetważania plików instrukcji (*.cmd)
 *
 * Klasa ta spełnia zadanie integracji programu z plikami .cmd
 * Pozwala na wczytywanie informacji zawartych w owych plikach.
 * W plikach znajdują się komendy dla programu, którę powinny zostać odczytane
 * przez program, a następnie zrealizowane. W przypadku nie rozpoznania powinien
 * zostać wyświetlony stosowny komunikat.
 *
 * Zadaniem głównym tej klasy jest:
 * - wczytanie pliku cmd
 * - przetworzenie pliku preprocesorem
 * - pobranie sekwencji instrukcji
 */

#include <iostream>
#include <sstream>
#include <cstring>
#include <fstream>
#include <vector>

#include <ext/stdio_filebuf.h>

/*!
 * \brief wprowadzamy model klasy instrukcji przynależnej do klasy głównej programu
 *
 * Klasa instrukcji określa w jaki sposób wczytujemy pliki instrukcji.
 * Wywołuje preprocesor dla wczytanego pliku
 */
class C_instrukcje{

/*!
 * \brief sekwencje instrukcji
 *
 * wektor wszystkich sekwencji instrukcji (prywatny)
 */
    std::vector<std::string> _sekwencje_instrukcji;

  public:

    /*!
     * \brief Metoda zwracająca liczbę wczytanych instrukcji
     *
     *  Odwołanie do metody size wektora sekwencji instrukcji
     *   \retval liczba dodatnia - całkowity rozmiar wektora instrukcji
     */
    unsigned pobierz_rozmiar_sekwencji_instrukcji();

    /*!
     * \brief Metoda zwracająca nazwę instrukcji wczytanej za i-tym razem
     *  \param[in] liczba dodatnia określająca numer wczytanej wcześniej instrukcji, której nazwa ma zostać wczytana
     *
     *  Odwołanie się do nazwy danej instrukcji po przez jej indeks
     *   \retval napis - nazwa instrukcji na i tym miejscu
     */
    std::string pobierz_sekwencje_instrukcji(unsigned i);

    /*!
     * \brief Metoda wczytująca nazwę pliku cmd
     *  \param[in] nazwa pliku - umożliwia niejawne wczytanie pliku (opcjonalnie)
     *
     *  Ta metoda umożliwia wczytanie nazwy pliku, jeśli plik nie znajduje sie w katalogu, w którym został wywołany
     *  Należy podać odpowienio ścieżkę dostępu adekwatną dla systemu, przed nazwą pliku
     *
     *  Wewnątrz tej metody zachodzi wczytania i wywołanie preprocesora dla podanego pliku
     */
    void wczytanie_nazwy_pliku_sekwencji_instrukcji_dla_drona(std::string nazwa_pliku = "");

    /*!
     * \brief Metoda wyświetlająca wczytane wcześniej sekwencje
     *
     *  Umożliwa wyświetlenie użytkownikowi w postaci jawnej danych uzyskanych po przetworzeniu pliku.
     */
    void pokaz_sekwencje_instrukcji();

};

#endif /// INSTRUKCJE_HH
