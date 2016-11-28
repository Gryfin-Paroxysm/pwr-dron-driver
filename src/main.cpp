#include <iostream>
#include <ctype.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

#include "pamiec_wspoldzielona.hh"
#include "opengl_window.hh"
#include "klasa_glowna.hh"

int global_shared_size;
struct shared_struct *global_shared_mem;

int main(int argc, char **argv)
{
    char *podany_plik_cmd = NULL;

    int znak;
    while((znak = getopt (argc, argv, "i:")) != -1)
        switch(znak)
        {
            case 'i': podany_plik_cmd = optarg; break;

            case '?':
                if (optopt == 'i')
                    std::cerr << "Opcja -" << (char)optopt << " wymaga argumentu." << std::endl;
                else if (isprint (optopt))
                    std::cerr << "Nieznana opcja `-" << optopt << "'." << std::endl;
                else
                    std::cerr << "Znak nie został rozpoznany: `\\x" << optopt << "'." << std::endl;
            break;

            default:
                std::cerr << "Coś poszło nie tak abort()" << std::endl;
                abort();
            break;
        }

    for(int i=optind;i<argc;i++)
        std::cout << "Brak opcji dla argumentu " << argv[i] << std::endl;

    if(podany_plik_cmd == NULL)
        podany_plik_cmd = (char*)"";
    /// -------

    C_opengl_window *gl;
    C_klasa_glowna *app;

    inicjalizacja_pamieci_wspolnej(global_shared_size, &global_shared_mem);

    pid_t pid;
    switch(pid = fork()){
        case -1:
            std::cout << "fork - nie powodzenie" << std::endl;
        break;

        case 0:
            app = new C_klasa_glowna();
            app->wczytaj_plik_cmd(podany_plik_cmd);
            app->start();
            delete app;
        break;

        default:
            gl = new C_opengl_window();
            gl->start_GL();
            delete gl;
        break;
    }

    deinicjalizacja_pamieci_wspolnej(global_shared_size, &global_shared_mem);
    return 0;
}
