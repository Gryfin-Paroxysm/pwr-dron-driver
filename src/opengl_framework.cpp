#include "opengl_framework.hh"

/// -------------------------------- PUBLIC -------------------------------- ///

C_opengl_framework::C_opengl_framework() : _szerokosc(),
                                           _wysokosc(),
                                           _nazwa_okna() ,
                                           _okno(),
                                           _klawisze(),
                                           _kamera_glowna()
{}

C_opengl_framework::~C_opengl_framework(){
    this->deinicjalizuj_GLFW();
}

void C_opengl_framework::inicjalizuj_C_opengl_framework(int szerokosc, int wysokosc, std::string nazwa_okna){
    _szerokosc = szerokosc;
    _wysokosc = wysokosc;
    _nazwa_okna = nazwa_okna;
    this->inicjalizuj_GLFW();
    this->inicjalizuj_GLEW();
}

bool C_opengl_framework::zamknieto_GLFW(){
    return glfwWindowShouldClose(this->_okno);
}

void C_opengl_framework::obsluga_zdarzen(){
    this->_kamera_glowna.przelicz_czas();

    glfwPollEvents();

    if(this->_klawisze[GLFW_KEY_W])
        this->_kamera_glowna.przemiesc(C_kamera_loader::KAMERA_PRZOD);
    if(this->_klawisze[GLFW_KEY_S])
        this->_kamera_glowna.przemiesc(C_kamera_loader::KAMERA_TYL);
    if(this->_klawisze[GLFW_KEY_A])
        this->_kamera_glowna.przemiesc(C_kamera_loader::KAMERA_LEWO);
    if(this->_klawisze[GLFW_KEY_D])
        this->_kamera_glowna.przemiesc(C_kamera_loader::KAMERA_PRAWO);

    glfwGetFramebufferSize(this->_okno,&this->_szerokosc,&this->_wysokosc);
    glViewport(0,0,this->_szerokosc,this->_wysokosc);
    this->_kamera_glowna._szerokosc = this->_szerokosc;
    this->_kamera_glowna._wysokosc = this->_wysokosc;

    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->rysuj_GL();

    glfwSwapBuffers(this->_okno);
}

/// -------------------------------- PROTECTED -------------------------------- ///

void C_opengl_framework::inicjalizuj_GL() {}
void C_opengl_framework::rysuj_GL() {}

/// -------------------------------- PRIVATE -------------------------------- ///

void C_opengl_framework::inicjalizuj_GLFW(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_RESIZABLE,GL_TRUE);
    this->_okno =
        glfwCreateWindow(this->_szerokosc,
                         this->_wysokosc,
                         this->_nazwa_okna.c_str(),nullptr,nullptr);
    glfwMakeContextCurrent(this->_okno);
    glfwSetKeyCallback(this->_okno,key_callback);
    glfwSetCursorPosCallback(this->_okno,mouse_callback);
    glfwSetScrollCallback(this->_okno,scroll_callback);
    glfwSetInputMode(this->_okno, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetWindowUserPointer(this->_okno, this);
}

void C_opengl_framework::deinicjalizuj_GLFW(){
    glfwDestroyWindow(this->_okno);
    glfwTerminate();
}

void C_opengl_framework::inicjalizuj_GLEW(){
    glewExperimental = GL_TRUE;
    glewInit();
    glEnable(GL_DEPTH_TEST);
}

void C_opengl_framework::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
    C_opengl_framework *GL = reinterpret_cast<C_opengl_framework*>(glfwGetWindowUserPointer(window));

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS) GL->_klawisze[key] = true;
        else if (action == GLFW_RELEASE) GL->_klawisze[key] = false;
    }
}

void C_opengl_framework::scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    C_opengl_framework *GL = reinterpret_cast<C_opengl_framework*>(glfwGetWindowUserPointer(window));

    if (GL->_kamera_glowna._przyblizenie >= 1.0f && GL->_kamera_glowna._przyblizenie <= 45.0f)
        GL->_kamera_glowna._przyblizenie -= yoffset;
    if (GL->_kamera_glowna._przyblizenie <= 1.0f)
        GL->_kamera_glowna._przyblizenie = 1.0f;
    if (GL->_kamera_glowna._przyblizenie >= 45.0f)
        GL->_kamera_glowna._przyblizenie = 45.0f;
}

void C_opengl_framework::mouse_callback(GLFWwindow* window, double xpos, double ypos){
    C_opengl_framework *GL = reinterpret_cast<C_opengl_framework*>(glfwGetWindowUserPointer(window));

    if (GL->_kamera_glowna._firstMouse){
        GL->_kamera_glowna._lastX = xpos;
        GL->_kamera_glowna._lastY = ypos;
        GL->_kamera_glowna._firstMouse = false;
    }

    GL->_kamera_glowna._yaw   -= (xpos - GL->_kamera_glowna._lastX) * 0.05;
    GL->_kamera_glowna._pitch -= (GL->_kamera_glowna._lastY - ypos) * 0.05;
    GL->_kamera_glowna.aktualizacja_parametrow();

    GL->_kamera_glowna._lastX = xpos;
    GL->_kamera_glowna._lastY = ypos;
}
