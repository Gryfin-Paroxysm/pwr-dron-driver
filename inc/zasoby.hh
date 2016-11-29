#ifndef  ZASOBY_HH
#define  ZASOBY_HH

/// SHADERY ///
const char* shader_v = "shadery/assimp.vs";
const char* shader_f = "shadery/assimp.fs";

const char* shader_skybox_v = "shadery/skybox.vs";
const char* shader_skybox_f = "shadery/skybox.fs";

/// MODELE 3D ///

const char* model_nanosuit = "modele/nanosuit/nanosuit.obj";
const char* model_dron = "modele/dron.obj";
const char* model_podloga = "modele/helipod.obj";

/// TEKSTURY ///

const char* tekstura_przeszkody = "modele/container.jpg";

/// SKYBOX ///

const char* skybox_right = "modele/skybox/right.jpg";
const char* skybox_left = "modele/skybox/left.jpg";
const char* skybox_top = "modele/skybox/top.jpg";
const char* skybox_bottom = "modele/skybox/bottom.jpg";
const char* skybox_back = "modele/skybox/back.jpg";
const char* skybox_front = "modele/skybox/front.jpg";

/// MODELE 3D przez definicje ///

GLfloat skybox[] = {
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

#endif /// ZASOBY_HH
