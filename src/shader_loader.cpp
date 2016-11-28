#include "shader_loader.hh"

C_shader_loader::C_shader_loader() : _program(),
                                     _kod_shadera_v(),
                                     _kod_shadera_f(),
                                     _vertex_shader_napis(),
                                     _fragment_shader_napis(){

}

void C_shader_loader::wczytaj_z_pliku(const GLchar* sciezka_do_v, const GLchar* sciezka_do_f){
    std::fstream shader_plik_v(sciezka_do_v);
    std::fstream shader_plik_f(sciezka_do_f);

    shader_plik_v.exceptions(std::ifstream::badbit);
    shader_plik_f.exceptions(std::ifstream::badbit);

    std::stringstream vertex_shader_strumien;
    std::stringstream fragment_shader_strumien;

    vertex_shader_strumien << shader_plik_v.rdbuf();
    fragment_shader_strumien << shader_plik_f.rdbuf();

    shader_plik_v.close();
    shader_plik_f.close();

    this->_vertex_shader_napis  = vertex_shader_strumien.str();
    this->_fragment_shader_napis = fragment_shader_strumien.str();

    this->_kod_shadera_v = this->_vertex_shader_napis.c_str();
    this->_kod_shadera_f = this->_fragment_shader_napis.c_str();

    GLuint shader_wierzcholkow = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shader_wierzcholkow, 1, &this->_kod_shadera_v,NULL);
    glCompileShader(shader_wierzcholkow);

    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader_wierzcholkow, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader_wierzcholkow, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    GLuint shader_fragmentow = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shader_fragmentow, 1, &this->_kod_shadera_f, NULL);
    glCompileShader(shader_fragmentow);

    glGetShaderiv(shader_fragmentow, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader_fragmentow, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    this->_program = glCreateProgram();
    glAttachShader(this->_program, shader_wierzcholkow);
    glAttachShader(this->_program, shader_fragmentow);
    glLinkProgram(this->_program);

    glDeleteShader(shader_wierzcholkow);
    glDeleteShader(shader_fragmentow);
}

void C_shader_loader::uzyj_program(){
    glUseProgram(this->_program);
}
