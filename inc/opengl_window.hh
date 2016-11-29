#ifndef  OPENGL_WINDOW_HH
#define  OPENGL_WINDOW_HH

#include "pamiec_wspoldzielona.hh"
#include "opengl_framework.hh"
#include "shader_loader.hh"
#include "model_loader.hh"

#include <string>
#include <vector>

class C_skybox{

	GLuint _vao;
    GLuint _vbo;
	std::vector<const GLchar*> faces;
	GLuint skyboxTexture;
	GLfloat skyboxVertices[200] = {
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

  public:

	C_skybox();
	void rysuj(C_shader_loader shader_model, C_kamera_loader kamera_glowna);

};

class C_proste_ksztalty{

    GLuint _vao;
    GLuint _vbo;
    GLfloat vertices[180];
    GLuint _tekstura;

    std::string _nazwa = "";
    GLfloat _pozycja_x = 0;
    GLfloat _pozycja_y = 0;
    GLfloat _pozycja_z = 0;
    GLfloat _rozmiar_x = 0;
    GLfloat _rozmiar_y = 0;
    GLfloat _rozmiar_z = 0;

  public:

    void stworz(std::string nazwa,GLfloat pozycja_x, GLfloat pozycja_y, GLfloat pozycja_z, GLfloat rozmiar_x, GLfloat rozmiar_y, GLfloat rozmiar_z);
	void rysuj(C_shader_loader shader_model, C_kamera_loader kamera_glowna);

};

class C_opengl_window : private C_opengl_framework{

    C_shader_loader _shader_model;

    C_shader_loader skyboxShader;
    C_skybox* skybox;

    C_model_loader* _model_nanosuit;
    C_model_loader* _model_dron;
    C_model_loader* _model_podloga;

    GLfloat x=0, y=0, z=0, yaw=0, pitch=0, roll=0;

  public:

    std::vector<C_proste_ksztalty> elementy_sceny;

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
