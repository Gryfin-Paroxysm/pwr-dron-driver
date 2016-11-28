#ifndef  WTYCZKI_HH
#define  WTYCZKI_HH

/*!
 * \file
 * \brief Klasa: C_wtyczki
 *
 * Plik zawierający definicję nagłówka klasy C_wtyczki,
 * która jest dziedziczona przez klasę C_klasa_glowna.
 * Zapewniając jej dodatkową funkcjonalność w zakresie
 * przetważania wtyczek (bibliotek dynamicznych)
 *
 * Klasa ta spełnia zadanie integracji programu z bibliotekami dynamicznymi
 * Pozwala na wczytywanie dodatkowych funkcjonalności dla programu za ich pomocą.
 *
 * Zadaniem głównym tej klasy jest:
 * - poprawne wczytywanie i usuwanie wtyczek
 * - wyswietlanie aktualnie dostępnych w programie wtyczek
 * - sprawdzanie czy dana wtyczka została już wczytana
 * - powiadamianie o błędach komunikacji programu z wtyczkami
 * - dodawania i usuwanie wtyczek z poziomu programu
 */

#include <iostream>
#include <dlfcn.h>
#include <map>

#include "wtyczka_loader.hh"

/*!
 * \brief wprowadzamy model klasy wtyczki przynależnej do klasy głównej programu
 *
 *  Klasa wtyczki określa w jaki sposób korzystamy z wtyczek (bibliotek dynamicznych współdzielonych)
 */
class C_wtyczki{

/*!
 * \brief wczytane pluginy
 *
 * Mapa wszystkich wczytanych pluginów (prywatny)
 */
    std::map<std::string,wtyczka_loader_struct*> _wczytane_pluginy;

/*!
 * \brief iterator wczytanych pluginów
 *
 * Ponieważ do przechowywania wczytywanych pluginów została zastosowana implementacja map,
 * Został zadeklarowany iterator dla niej. (prywatny)
 */
    std::map<std::string,wtyczka_loader_struct*>::iterator _it;

  public:

    /*!
     * \brief Metoda umożliwiająca bezpośreni dostęp przez pole prywatne do odnośnika wczytanego pluginu
     *  \param[in] nazwa instrukcji - nazwa wtyczki (zakładamy, że każda nazwa instrukcji jest tożsama z nazwą wtyczki)
     *
     *  Dostęp przez pole prywatne do struktury wtyczki. Umożliwia wywołanie funkcji dostępnych we wtyczkach.
     *   \retval struktura wtyczki - zwracany jest wskaźnik na strukturę wtyczki, co umożliwia operacje na niej.
     */
    wtyczka_loader_struct* odnosnik_do_wczytanego_pluginu(std::string nazwa_instrukcji);

    /*!
     * \brief Metoda pokazująca dostępne wtyczki
     *
     *  Jawne wyświetlenie użytkownikowi, jakie wtyczki zostały wczytane.
     */
    void pokaz_dostepne_wtyczki();

    /*!
     * \brief Metoda dodająca nową wtyczkę
     *  \param[in] nazwa pluginu (opcjonalnie) - do wczytywania niejawnego dla użytkownika
     *
     *  Dodaje wtyczkę, uzupełnia odpowiednie powiązania i zapewnia dostęp pamięci do wtyczki.
     *  Umożliwia komunikację programu z wtyczką.
     */
    void dodaj_nowa_wtyczke(std::string nazwa_pluginu = "");

    /*!
     * \brief Metoda usuwająca wtyczkę
     *
     *  Usuwa wtyczkę z mapy oraz czyści wszystkie odwołania do wtyczki.
     *  Po użyciu tej metody nie jest już możliwe skorzystanie z wtyczki.
     *  Należy ją ponownie dodać w przypadku chęci ponownego skorzystania z niej.
     */
    void usun_wtyczke();

    /*!
     * \brief Metoda sprawdzająca czy dana wtyczka została załadowana
     *  \param[in] nazwa pluginu - podana fraza będzie wyszukiwana w mapie wtyczek
     *
     *  Metoda pozwalająca na przeszukiwanie mapy wtyczek podaną frazą.
     *   \retval prawda - jeśli udało się odnaleźć podaną frazę w mapie wtyczek
     */
    bool sprawdz_czy_zaladowana(std::string nazwa_pluginu);

  private:

    /*!
     * \brief Metoda powiadamiająca o błędach biblioteki dlfcn
     *  \param[in] napis poprzedzający komunikat o błędzie (opcjonalny)
     *
     *  Sprawdza czy nie wystąpił błąd bliblioteki dynamicznej, jeśli nie to kontynuuje się 
     *  działanie programu. Skraca zapis kodu. Domyślnie wyświetlany jest tylko komunikat pochodzący
     *  z biblioteki dlfcn, natomiast jest możliwe poprzedzenie tego komunikatu własnym.
     *   \retval prawda - jeśli wystąpił jakiś błąd związany z obsługą bibliotek dynamicznych
     */
    bool blad_dlfcn(const char* napis = "");

};

#endif /// WTYCZKI_HH
