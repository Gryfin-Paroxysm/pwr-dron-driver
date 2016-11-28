#include "opengl_window.hh"

#include "zasoby.hh"
extern struct shared_struct *global_shared_mem;

C_opengl_window::C_opengl_window()
{
    this->inicjalizuj_C_opengl_framework();
    this->inicjalizuj_GL();
    this->obsluga_zdarzen();
}

C_opengl_window::~C_opengl_window(){
    delete _model_nanosuit;
    delete _model_dron;
    delete _model_podloga;
}

void C_opengl_window::start_GL(){
    while(!this->zamknieto_GLFW())
        this->obsluga_zdarzen();
}

void C_opengl_window::inicjalizuj_GL(){

    _shader_model.wczytaj_z_pliku(shader_v,shader_f);

    _model_nanosuit = new C_model_loader(model_nanosuit);
    _model_dron = new C_model_loader(model_dron);
    _model_podloga = new C_model_loader(model_podloga);

}

void C_opengl_window::rysuj_GL(){
    std::string napis_ = pobierz_informacje_z_pamieci();

    if(napis_ != ""){
        std::cout << "odebrano: " << napis_ << std::endl;

        if(napis_ == "koniec")
            { /*zamknąć okno*/ }

        std::stringstream strumien;
        strumien << napis_;

        char srednik, zadanie;
        strumien >> zadanie >> srednik;

        std::string nazwa_przeszkody = "";
        GLfloat pozycja_x = 0;
        GLfloat pozycja_y = 0;
        GLfloat pozycja_z = 0;
        GLfloat rozmiar_x = 0;
        GLfloat rozmiar_y = 0;
        GLfloat rozmiar_z = 0;

        switch(zadanie)
        {
            case 's':
                strumien >> x >> srednik >> y >> srednik >> z >> srednik >> pitch;
            break;

            case 'p':
                strumien >> nazwa_przeszkody >> pozycja_x >> pozycja_y >> pozycja_z >> rozmiar_x >> rozmiar_y >> rozmiar_z;
                /// utwórz przeszkode
            break;

            default:
            break;
        }
    }

    //_model_nanosuit->rysuj(_shader_model,_kamera_glowna,x,y,z,yaw,-pitch,roll);
    _model_dron->rysuj(_shader_model,_kamera_glowna,x,y,z,yaw,pitch,roll);
    _model_podloga->rysuj(_shader_model,_kamera_glowna,0,-2.1,0,0,0,0);
    /// rysuj przeszkode

}

std::string C_opengl_window::pobierz_informacje_z_pamieci(void){
    if (global_shared_mem->client_wrote) {
        global_shared_mem->client_wrote = 0;
        return global_shared_mem->text;
    }
    return "";
}
