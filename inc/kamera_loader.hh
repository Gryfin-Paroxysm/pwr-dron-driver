#ifndef  KAMERA_LOADER_HH
#define  KAMERA_LOADER_HH

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/matrix_transform.hpp>

class C_kamera_loader{

  public:

    glm::vec3 _pozycja;
    glm::vec3 _do_przodu;
    glm::vec3 _w_gore;
    glm::vec3 _w_prawo;
    glm::vec3 _celownik;

    glm::float32 _roll;
    glm::float32 _pitch;
    glm::float32 _yaw;

    glm::float32 _przyblizenie;
    glm::float32 _czulosc;

    bool _firstMouse;
    glm::float32 _lastX;
    glm::float32 _lastY;

    glm::float32 _deltaTime;
    glm::float32 _lastFrame;
    glm::float32 _currentFrame;

    GLfloat _szerokosc;
    GLfloat _wysokosc;

    enum sterowanie_enum{
        KAMERA_PRZOD,
        KAMERA_TYL,
        KAMERA_GORA,
        KAMERA_DOL,
        KAMERA_PRAWO,
        KAMERA_LEWO,

        KAMERA_ROLL_MINUS,
        KAMERA_ROLL_PLUS,
        KAMERA_PITCH_MINUS,
        KAMERA_PITCH_PLUS,
        KAMERA_YAW_MINUS,
        KAMERA_YAW_PLUS
    };

    C_kamera_loader(glm::vec3    pozycja      = glm::vec3( 5.0f,  5.0f,  0.0f),
                  glm::vec3    do_przodu    = glm::vec3( 0.0f,  0.0f,  1.0f),
                  glm::vec3    w_gore       = glm::vec3( 0.0f,  1.5f,  0.0f),
                  glm::float32 roll         =  180.0f,
                  glm::float32 pitch        =  3.0f,
                  glm::float32 yaw          =  4.5f,
                  glm::float32 przyblizenie =  4.5f,
                  glm::float32 czulosc      =   0.01f
                  );

    glm::mat4 macierz_lookAt();
    void przemiesc(sterowanie_enum argument);
    void przelicz_czas();
    void aktualizacja_parametrow();
};

#endif /// KAMERA_LOADER_HH
