#ifndef  KLASA_GLOWNA_HH
#define  KLASA_GLOWNA_HH

/*!
 * \file
 * \brief Klasa: C_klasa_glowna
 *
 * Plik zawierający definicję nagłówka klasy C_klasa_glowna, która dziedziczy
 * dodatkową funkcjonalność po klasach C_instrukcje oraz C_wtyczki.
 *
 * Klasa ta spełnia zadanie podstawowej interakcji z użytkownikiem.
 * Pozwala na wczytywanie wtyczek oraz wczytywanie plików z zadaniami.
 * Ponadto klasa wprowadza możliwość komunikacji przez pamięć
 * współdzieloną z oknem OpenGl otwartym w potomku.
 * By pozwolić wtyczką na interakcje ze sterowanym obiektem należy przekazać
 * wskaźnik do tej pamięci. Klasa sterowanego obiektu:
 * C_dron jest biblioteką statyczną napisaną w stylu PIC i należy ją dolinkować do wtyczki.
 *
 * Zadaniem głównym tej klasy jest:
 * - wyswietlenie menu,
 * - wyswietlenie zapytania dla użytkownika
 * - wystartowanie wczytanego zadania
 * - bezpośrednia komunikacja ze środowiskiem potomnym OpenGL
 * - wprowadzenie łącznika pamięci współdzielonej dla rodzica
 */

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <readline/readline.h>
#include <readline/history.h>

#include "pamiec_wspoldzielona.hh"
#include "instrukcje.hh"
#include "wtyczki.hh"

extern struct shared_struct *global_shared_mem;

/*!
 * \brief wprowadzamy model klasy głównej naszego programu
 *
 * Klasa główna określa menu oraz sposób interakcji z użytkownikiem
 * Wywołuje resztę zdefiniowanych zadań przewidzianych dla wprowadzania
 * danych mających charakter definiujący dla okna graficznego.
 */
class C_klasa_glowna : private C_instrukcje, private C_wtyczki{

/*!
 * \brief plik cmd
 *
 * To pole umożliwia wczytanie pliku z poziomu wywołania programu
 */
    string _plik_cmd = "";

  public:

    /*!
     * \brief Metoda wywołująca pętlę główną
     *
     * Nieskończona pętla główna wywołująca zapytanie dla użytkownika,
     * Pętla kończy się w momencie gdy pojawi się znak 'k' na standardowym wejściu
     * jako odpowiedź dla zapytania. Jest to w całości kontrolowane przez użytkownika.
     * Wyjątkiem jest zamknięcie okna OpenGl, spowoduje to automatyczne zamknięcię programu.
     */
    void start();

    /*!
     * \brief Metoda umożliwiająca uzupełnienie zmiennej plik)cmd
     *  \param[in] nazwa pliku cmd
     *
     * Metoda umożliwia wczytanie pliku z poziomu wywołania programu.
     * Jej wywołanie nie jest konieczne.
     */
    void wczytaj_plik_cmd(std::string nazwa_pliku_cmd);

  private:

    /*!
     * \brief Metoda wyświetlająca menu
     *
     * Proste wyswietlenie menu, wywołane na standardowe wyjście
     */
    void wyswietl_menu();

    /*!
     * \brief Metoda pytająca użytkownika o wybór opbji z menu
     *
     * Prostę pobieranie pojedynczego znaku ze standardowego wejścia.
     * Metodzie toważyszy asercja dla znaku końca lini (EOF)
     * Po tym znaku program automatycznie kończy pracę.
     *   \retval char - znak który został wprowadzony na standardowe wejście przez użytkownika
     */
    char zapytanie();

    /*!
     * \brief Metoda wywołująca start wykonywania sekwencji
     *
     * Metoda kolejno sprawdza wczytane komendy z pliku i wywołuje odpowiednio
     * funkcje dla niej, jest wywoływana funkcja o symbolu nazwy instrukcji.
     * W momencie gdy nie zostanie znaleziona biblioteka zawierająca
     * owy symbol, metoda kończy swoje działanie.
     */
    void start_wykonywania_sekwencji_instrukcji();

    /*!
     * \brief Metoda pozwalająca na bezpośrednią interakcję z obiektem w potomku
     *
     * Metoda przewidziana dla zerowania ustawień drona, pozwala również na
     * sterowanie dronem w sposób ręczny.
     */
    void sterowanie_dronem();

    /*!
     * \brief Metoda obsługująca menu
     *
     * Metoda pozwalająca na obsługę menu. Jako parametr przyjmuje
     * pojedynczy znak, który decyduje o wywołaniu zadania do wykonania.
     * W momencie nie rozpoznania znaku pojawia się stosowny komunikat,
     * o braku jego implementacji.
     *  \param[in] opcja - charakteryzuje wybraną opcję w menu
     *  \retval false - jeśli nie wybrano opcji kończącej działanie programu ('k')
     */
    bool obsluga_opcji_menu(char opcja);

    /*!
     * \brief Metoda przekazująca informacje do pamięci współdzielonej
     *
     * Metoda pozwalająca na przekazanie informacji dla potomka.
     * Zaimplementowana metoda jest jednokierunkowa i dotyczy przejścia informacji
     * Tylko z rodzica do potomka.
     *
     *  \param[in] napis - charakteryzuje ciąg przesyłanych komend
     *               w stylu: x;y;z;a
     *  gdzie: x,y,z to współrzędne kartejańskie pozycji modelu,
     *         a to kąt alfa - opisujący rotacje yaw
     *
     * UWAGA: należy pamiętać, że środowisko OpenGl ma zamienione osie z oraz y,
     * obsługa tej zależności powinna zostać wykonana na własną rękę
     */
    void przekaz_informacje_do_pamieci(std::string napis);

    void wczytaj_podstawowe_wtyczki();

};

#endif /// KLASA_GLOWNA_HH
