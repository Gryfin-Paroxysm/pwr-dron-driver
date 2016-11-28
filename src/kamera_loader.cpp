#include "kamera_loader.hh"

C_kamera_loader::C_kamera_loader(
        glm::vec3    pozycja,
        glm::vec3    do_przodu,
        glm::vec3    w_gore,
        glm::float32 roll,
        glm::float32 pitch,
        glm::float32 yaw,
        glm::float32 przyblizenie,
        glm::float32 czulosc
        ) : _pozycja(pozycja),
            _do_przodu(do_przodu),
            _w_gore(w_gore),
            _roll(roll),
            _pitch(pitch),
            _yaw(yaw),
            _przyblizenie(przyblizenie),
            _czulosc(czulosc),
            _firstMouse(true),
            _lastX(0),
            _lastY(0),
            _deltaTime(0),
            _lastFrame(0),
            _currentFrame(0)
    {
    this->aktualizacja_parametrow();
}

glm::mat4 C_kamera_loader::macierz_lookAt(){
    return glm::lookAt(this->_pozycja, this->_celownik, this->_w_gore);
}

void C_kamera_loader::przemiesc(sterowanie_enum argument){
    switch (argument){
        case KAMERA_PRZOD: { _pozycja += _do_przodu; }break;
        case KAMERA_TYL:   { _pozycja -= _do_przodu; }break;
        case KAMERA_GORA:  { _pozycja += _w_gore;    }break;
        case KAMERA_DOL:   { _pozycja -= _w_gore;    }break;
        case KAMERA_PRAWO: { _pozycja -= _w_prawo;   }break;
        case KAMERA_LEWO:  { _pozycja += _w_prawo;   }break;

        case KAMERA_ROLL_MINUS:  { _roll--;  }break;
        case KAMERA_ROLL_PLUS:   { _roll++;  }break;
        case KAMERA_PITCH_MINUS: { _pitch--; }break;
        case KAMERA_PITCH_PLUS:  { _pitch++; }break;
        case KAMERA_YAW_MINUS:   { _yaw--;   }break;
        case KAMERA_YAW_PLUS:    { _yaw++;   }break;

        default: {} break;
    }
    this->aktualizacja_parametrow();
}

void C_kamera_loader::aktualizacja_parametrow(){
    glm::mat4 macierz_rotacji = glm::yawPitchRoll(glm::radians(_yaw),glm::radians(_pitch),glm::radians(_roll));
    _do_przodu = _czulosc * glm::normalize(glm::vec3(macierz_rotacji * glm::vec4(0,0,1,0)));
    _w_gore    = _czulosc * glm::normalize(glm::vec3(macierz_rotacji * glm::vec4(0,1,0,0)));
    _w_prawo   = _czulosc * glm::normalize(glm::cross(_do_przodu, _w_gore));
    _celownik  = _pozycja + _do_przodu;
}

void C_kamera_loader::przelicz_czas(){
    _currentFrame = glfwGetTime();
    _deltaTime = _currentFrame - _lastFrame;
    _lastFrame = _currentFrame;
    _czulosc = 5.0f * _deltaTime;
}
