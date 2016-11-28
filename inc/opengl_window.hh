#ifndef  OPENGL_WINDOW_HH
#define  OPENGL_WINDOW_HH

#include "pamiec_wspoldzielona.hh"
#include "opengl_framework.hh"
#include "shader_loader.hh"
#include "model_loader.hh"

class C_opengl_window : private C_opengl_framework{

    C_shader_loader _shader_model;

    C_model_loader* _model_nanosuit;
    C_model_loader* _model_dron;
    C_model_loader* _model_podloga;

    GLfloat x=0, y=0, z=0, yaw=0, pitch=0, roll=0;

  public:

    C_opengl_window();
    ~C_opengl_window();

    void start_GL();

  protected:

  private:

    void inicjalizuj_GL();
    void rysuj_GL();

    std::string pobierz_informacje_z_pamieci(void);
};

#endif /// OPENGL_WINDOW_HH
