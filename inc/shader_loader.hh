#ifndef  SHADER_LOADER_HH
#define  SHADER_LOADER_HH

#include <iostream>
#include <sstream>
#include <fstream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/matrix_transform.hpp>

class C_shader_loader{
  public:
    GLuint _program;
    const GLchar* _kod_shadera_v;
    const GLchar* _kod_shadera_f;
    std::string _vertex_shader_napis;
    std::string _fragment_shader_napis;

    C_shader_loader();

    void wczytaj_z_pliku(const GLchar* sciezka_do_v, const GLchar* sciezka_do_f);
    void uzyj_program();
};

#endif /// SHADER_LOADER_HH
