#include "klasa_glowna.hh"

/*!
 * \file
 * \brief Definicja klasy: C_klasa_glowna
 *
 * Plik zawierający definicję klasy C_klasa_glowna, która dziedziczy
 * dodatkową funkcjonalność po klasach C_instrukcje oraz C_wtyczki.
 *
 * W związku z tym dziedziczeniem, wybrane funkcje są dostępne z innych klas.
 */

/*!
 * Jednorazowe wyświetlenie menu, a następnie wejście w nieskończoną pętle,
 * wywołującą zapytanie dla użytkownika.
 */
void C_klasa_glowna::start(){
    rl_bind_key('\t',rl_complete);

    wczytaj_podstawowe_wtyczki();
    if(_plik_cmd != ""){
        wczytanie_nazwy_pliku_sekwencji_instrukcji_dla_drona(_plik_cmd);
        start_wykonywania_sekwencji_instrukcji();
        przekaz_informacje_do_pamieci("koniec");
    }
    else
    {
        wyswietl_menu();
        while(obsluga_opcji_menu(zapytanie()));
    }
}

/*!
 * Uzupełnienie pola prywatnego
 */
void C_klasa_glowna::wczytaj_plik_cmd(std::string nazwa_pliku_cmd){
    _plik_cmd = nazwa_pliku_cmd;
}

/*!
 * Wyświetlanie menu
 */
void C_klasa_glowna::wyswietl_menu(){
    std::cout << "                                                          " << std::endl;
    std::cout << " w - wczytanie nazwy pliku sekwencji instrukcji dla drona " << std::endl;
    std::cout << " p - pokaz sekwencje instrukcji                           " << std::endl;
    std::cout << " i - pokaz dostepne wtyczki                               " << std::endl;
    std::cout << " s - start wykonywania sekwencji instrukcji               " << std::endl;
    std::cout << " a - dodaj nowa wtyczke                                   " << std::endl;
    std::cout << " d - usun wtyczke                                         " << std::endl;
    std::cout << " ? - wyswietl ponownie menu                               " << std::endl;
    std::cout << " [extras] g - sterowanie dronem                           " << std::endl;
    std::cout << "                                                          " << std::endl;
    std::cout << " k - koniec dzialania programu                            " << std::endl;
    std::cout << "                                                          " << std::endl;
}

/*!
 * Metoda umożliwijaca wybór opcji z menu
 *
 * \return Zwraca znak wpisany przez użytkownika na standardowe wyjście.
 */
char C_klasa_glowna::zapytanie(){
    char wybor_w_menu;
    std::istringstream strumien_wejsciowy;

    char* linia_polecenia = readline("Twój wybór (? - menu): ");
    if(!linia_polecenia) return 'k';
    add_history(linia_polecenia);
    strumien_wejsciowy.str(linia_polecenia);
    free(linia_polecenia);

    strumien_wejsciowy >> wybor_w_menu;

    if(strumien_wejsciowy.eof()){
        std::cout << "Okno OpenGL zostało zamknięte, kończenie pracy programu" << std::endl;
        wybor_w_menu = 'k';
    }
    return wybor_w_menu;
}

/*!
 * Metoda startująca główne zadanie programu.
 * - tworzony jest nowy obiekt klasy C_dron
 * - tworzony jest plik o nazwie output.cmd w którym pojawi się wynik obliczeń po wykonaniu zadania
 * - z póli wczytanych komend, wyszukuje się odpowiednią wtyczkę i wywołuje się jej zadanie
 */
void C_klasa_glowna::start_wykonywania_sekwencji_instrukcji(){
    C_dron *dron;
    dron = new C_dron;
    dron->polacz_komunikacje(global_shared_mem);

    std::fstream plik("output.cmd", ios::out | ios::trunc);

    for(unsigned i=0;i<pobierz_rozmiar_sekwencji_instrukcji();i++){
        std::string instrukcja = pobierz_sekwencje_instrukcji(i);

        std::stringstream strumien_instrukcji;
        strumien_instrukcji << instrukcja;

        std::string nazwa_instrukcji;
        strumien_instrukcji >> nazwa_instrukcji;

        if(!sprawdz_czy_zaladowana(nazwa_instrukcji)){
            std::cerr << "Nie odnaleziono wymaganej biblioteki" << std::endl;
            plik.close();
            return;
        }

        if(!odnosnik_do_wczytanego_pluginu(nazwa_instrukcji)->_wskaznik_do_pluginu->odczytaj_komende(strumien_instrukcji)){
            std::cerr << "nie udało się wczytać instrukcji:" << nazwa_instrukcji << std::endl;
            plik.close();
            return;
        }

        if(!odnosnik_do_wczytanego_pluginu(nazwa_instrukcji)->_wskaznik_do_pluginu->wykonaj_komende(dron)){
            std::cerr << "błąd wykonywania komendy" << std::endl;
            plik.close();
            return;
        }

        dron->zapisz_pozycje_w_pliku(plik);
    }
    plik.close();

    std::cout << "Udało się zrealizować zadanie" << std::endl;
}

/*!
 * Metoda startująca obiektem w potomku ręcznie
 * Za pomocą standardowego wejścia pobiera się od użytkownika parametry pozycji
 * a następnie przekazuje się je do drona.
 */
void C_klasa_glowna::sterowanie_dronem(){
    std::cout << "podaj parametry dla drona: " << std::endl;
    std::cout << "x: "; double x; std::cin >> x;
    std::cout << "y: "; double y; std::cin >> y;
    std::cout << "z: "; double z; std::cin >> z;
    std::cout << "alfa: "; double a; std::cin >> a;
    stringstream strumien_informacji;
    char srednik = ';';
    strumien_informacji << x << srednik << y << srednik << z << srednik << a;
    string infromacja = strumien_informacji.str();
    przekaz_informacje_do_pamieci(infromacja);
}

/*!
 * Metoda obsługująca wybór użytkownika, przyjmuje pojedynczy znak jako parametr.
 * W zależności od wartości znaku uruchomiona zostaje zdefiniowana metoda.
 */
bool C_klasa_glowna::obsluga_opcji_menu(char opcja){
    switch(opcja)
    {
        case 'w':
            wczytanie_nazwy_pliku_sekwencji_instrukcji_dla_drona();
        break;

        case 'p':
            pokaz_sekwencje_instrukcji();
        break;

        case 'i':
            pokaz_dostepne_wtyczki();
        break;

        case 's':
            start_wykonywania_sekwencji_instrukcji();
        break;

        case 'a':
            dodaj_nowa_wtyczke();
        break;

        case 'd':
            usun_wtyczke();
        break;

        case '?':
            wyswietl_menu();
        break;

        case 'g':
            sterowanie_dronem();
        break;

        case 'k':
            return false;
        break;

        default:
            std::cout << "opcja nieznana, operacja nie powiodła się" << std::endl;
        break;
    }
    return true;
}

/*!
 * Metoda przekazująca informacje do pamięci współdzielonej
 * Jest wykorzystywana do komunikacji z oknem OpenGl
 */
void C_klasa_glowna::przekaz_informacje_do_pamieci(std::string napis){
    while(global_shared_mem->client_wrote == 1) {}
    strcpy(global_shared_mem->text, napis.c_str());
    global_shared_mem->client_wrote = 1;
}

void C_klasa_glowna::wczytaj_podstawowe_wtyczki(){
    dodaj_nowa_wtyczke("Fly");
    dodaj_nowa_wtyczke("Rotate");
    dodaj_nowa_wtyczke("Turn");
    dodaj_nowa_wtyczke("Scene");
    dodaj_nowa_wtyczke("Pause");
}
