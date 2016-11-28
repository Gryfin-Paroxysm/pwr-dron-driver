#ifndef  MODEL_LOADER_HH
#define  MODEL_LOADER_HH

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <SOIL.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "shader_loader.hh"
#include "kamera_loader.hh"

#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include <map>
#include <vector>

struct wierzcholek{
    glm::vec3 _wspolrzedne;
    glm::vec3 _normalne;
    glm::vec2 _koordynaty_tekstury;
};

struct tekstura{
    GLuint _id;
    std::string _typ;
    aiString _sciezka;
};

class C_bryla{

    GLuint _vao;
    GLuint _vbo;
    GLuint _ebo;

  public:

    std::vector<wierzcholek> _wierzcholki;
    std::vector<GLuint> _polaczenia;
    std::vector<tekstura> _tekstury;

    C_bryla(std::vector<wierzcholek> wierzcholki, std::vector<GLuint> polaczenia, std::vector<tekstura> tekstury);
    void rysuj(C_shader_loader shader_modelu, C_kamera_loader kamera_glowna, GLfloat x, GLfloat y, GLfloat z, GLfloat ya, GLfloat pi, GLfloat ro);

  private:

    void inicjalizuj_bryle();

};

class C_model_loader{

    std::vector<C_bryla> _bryly;
    std::string _folder;
    std::vector<tekstura> _tekstury_wczytane;

  public:

    C_model_loader(const char* sciezka);

    void rysuj(C_shader_loader shader_modelu, C_kamera_loader kamera_glowna, GLfloat x, GLfloat y, GLfloat z, GLfloat ya, GLfloat pi, GLfloat ro);

  private:

    void wczytaj_model(std::string sciezka);
    void przeszukaj_wezly(aiNode* wezel, const aiScene* scena);
    C_bryla wczytaj_bryle(aiMesh* bryla, const aiScene* scena);
    std::vector<tekstura> wczytaj_material(aiMaterial* material, aiTextureType typ, std::string nazwa_typu);
    GLint wczytaj_teksture_z_pliku(const char* sciezka, std::string folder);

};

#endif /// MODEL_LOADER_HH
