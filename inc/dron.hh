#ifndef  DRON_HH
#define  DRON_HH

/*!
 * \file
 * \brief Klasa: C_dron
 *
 * Plik zawierający definicję nagłówka klasy C_dron,
 * która jest wykorzystywana przez wtyczki do kontorli obiektem.
 * Zapewniając funkcjonalność sterowania dronem i przechowywania w nim informacji.
 *
 * Zadaniem głównym tej klasy jest:
 * - ustawianie współrzędnych obiektu drona
 * - wyświetlenie informacyjnie pozycji
 * - zapewnienie komunikacji z procesem podrzędnym za pomocą pamięci współdzielonej
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>

#include "pamiec_wspoldzielona.hh"
#include "scena.hh"
#include "punkt.hh"

/*!
 * \brief wprowadzamy model klasy drona
 *
 *  Klasa modeluje pojęcie drona.
 */
class C_dron{

/*!
 * \brief współrzędne
 *
 * Zawiera informacje o aktualnej pozycji drona w układzie globalnym (świata)
 */
    punkt_struct _wspolrzedne;

/*!
 * \brief kąt obrotu osi yaw drona, wyrażony w stopniach
 *
 * Zawiera informacje o kącie obrotu od osi x drona
 */
    double _kat_w_stopniach = 0;

/*!
 * \brief wskaźnik do deklarowanej globalnie pamięci współdzielonej
 *
 * Umożliwia komunikację przez pamięć współdzieloną z procesem potomnym
 */
    struct shared_struct *global_shared_mem;

  public:

    C_scena _scena;

    /*!
     * \brief Metoda ustawiająca współrzędne obiektu
     *
     *  Pozwala na dostęp do pola prywatnego współrzędnych.
     *  Odwołanie się za pomocą wartości x,y,z
     */
    void ustaw_wspolrzedne(double x, double y, double z);

    /*!
     * \brief Metoda ustawiająca współrzędne obiektu
     *  \param[in] współrzędne - wejściowe informacje o pozycji za pomocą struktury punktu
     *
     *  Pozwala na dostęp do pola prywatnego współrzędnych.
     *  Odwołanie się za pomocą wartości punktu
     */
    void ustaw_wspolrzedne(const punkt_struct& wspolrzedne);

    /*!
     * \brief Metoda ustawiająca kąt, wartość powinna zostać podana w stopniach
     *  \param[in] kąt w stopniach - kąt obrotu o oś z
     *
     *  Obraca obiekt drona o podany kąt. Podany kąt jest liczony zawsze od osi x,
     *  nie jest to wartość inkrementowalna.
     */
    void ustaw_kat_w_stopniach(double kat_w_stopniach);

    /*!
     * \brief Metoda zwracająca aktualną pozycję obiektu
     *
     *  Pozwala na otrzymanie danych w których aktualnie przebywa obiekt,
     *  Jest to pozycja globalna.
     *   \retval punkt - aktualna pozycja obiektu
     */
    punkt_struct wspolrzedne() const;

    /*!
     * \brief Metoda zwracająca aktualnieaktywny kąt obrotu drona wyrażony w stopniach
     *
     *  Pozwala na otrzymanie kąta obrotu, który aktualnie posiada obiekt.
     *  Obrót dotyczy rotacji yaw - kąt Eulera
     *   \retval kąt - aktualny kąt obrotu drona (stopnie)
     */
    double kat_w_stopniach() const;

    /*!
     * \brief Metoda zapisująca daną pozycję i kąt obrotu obiektu w pliku
     *  \param[out] strumień pliku - do tego strumienia zostaną przekazane dane o aktualnej pozycji robota
     *
     *  Pozwala na zapis aktualnej pozycji w pliku.
     */
    void zapisz_pozycje_w_pliku(std::fstream& plik);

    /*!
     * \brief Metoda wyświetlająca aktualną pozycję
     *
     *  Pozwala na jawne wyświetlenie użytkownikowi pozycji obiektu.
     */
    void wyswietl_pozycje();

    /*!
     * \brief Metoda łącząca komunikację obiektu z procesem - dzieckiem
     *  \param[in] wskaźnik na strukturę pamięci dynamicznej
     *
     *  Pozwala na połączenie wtyczek z możliwościami OpenGL
     */
    void polacz_komunikacje(struct shared_struct *lacznik_shared_mem);

    /*!
     * \brief Metoda przesyłająca informacje do pamięci współdzielonej
     *  \param[in] napis - ciąg znaków wprowadzający informację do procesu potomnego.
     *
     *  Pozwala na komunikację z OpenGL. Ciąg znaków jest zdefiniowany za pomocą ramki danych,
     *  Która wygląda następująco: x;y;z;yaw
     *  Kolejno parametry pozycji x y z oraz obrotu są podawane i oddzielane znakiem średnika (;)
     */
    void przekaz_informacje_do_pamieci(std::string napis);

};

#endif /// DRON_HH
