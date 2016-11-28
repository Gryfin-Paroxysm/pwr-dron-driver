#ifndef  OPENGL_FRAMEWORK_HH
#define  OPENGL_FRAMEWORK_HH

#include <iostream>
#include <sstream>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "kamera_loader.hh"

class C_opengl_framework{

    int _szerokosc;
    int _wysokosc;
    std::string _nazwa_okna;
    GLFWwindow* _okno;
    bool _klawisze[1024];

  public:

    C_kamera_loader _kamera_glowna;

    C_opengl_framework();
    virtual ~C_opengl_framework();

    void inicjalizuj_C_opengl_framework(int szerokosc = 512, int wysokosc = 512, std::string nazwa_okna = "OpenGL - Window");
    bool zamknieto_GLFW();
    void obsluga_zdarzen();

  protected:

    virtual void inicjalizuj_GL();
    virtual void rysuj_GL();

  private:

    void inicjalizuj_GLFW();
    void deinicjalizuj_GLFW();
    void inicjalizuj_GLEW();

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

};

#endif /// OPENGL_FRAMEWORK_HH
