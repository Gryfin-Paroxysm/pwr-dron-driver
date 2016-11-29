#include "opengl_window.hh"

#include "zasoby.hh"
extern struct shared_struct *global_shared_mem;

C_skybox::C_skybox(){
    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);
    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glBindVertexArray(0);

    faces.push_back(skybox_right);
    faces.push_back(skybox_left);
    faces.push_back(skybox_top);
    faces.push_back(skybox_bottom);
    faces.push_back(skybox_back);
    faces.push_back(skybox_front);

	glGenTextures(1, &skyboxTexture);

	int width,height;
	unsigned char* image;

	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
	for(GLuint i = 0; i < faces.size(); i++)
	{
	    image = SOIL_load_image(faces[i], &width, &height, 0, SOIL_LOAD_RGB);
	    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	    SOIL_free_image_data(image);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void C_skybox::rysuj(C_shader_loader skyboxShader, C_kamera_loader kamera_glowna){
    glDepthFunc(GL_LEQUAL);
    skyboxShader.uzyj_program();
    glm::mat4 view = glm::mat4(glm::mat3(kamera_glowna.macierz_lookAt()));
    glUniformMatrix4fv(glGetUniformLocation(skyboxShader._program, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glm::mat4 projection = glm::perspective(kamera_glowna._przyblizenie, kamera_glowna._szerokosc/kamera_glowna._wysokosc, 0.1f, 100.0f);
    glUniformMatrix4fv(glGetUniformLocation(skyboxShader._program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glBindVertexArray(_vao);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS);
}

void C_proste_ksztalty::stworz(std::string nazwa,GLfloat pozycja_x, GLfloat pozycja_y, GLfloat pozycja_z, GLfloat rozmiar_x, GLfloat rozmiar_y, GLfloat rozmiar_z){
    _nazwa = nazwa;
    _pozycja_x = pozycja_x;
    _pozycja_y = pozycja_y;
    _pozycja_z = pozycja_z;
    _rozmiar_x = rozmiar_x;
    _rozmiar_y = rozmiar_y;
    _rozmiar_z = rozmiar_z;

    vertices[3] = 0.0f; vertices[4] = 0.0f;
    vertices[8] = 1.0f; vertices[9] = 0.0f;
    vertices[13] = 1.0f; vertices[14] = 1.0f;
    vertices[18] = 1.0f; vertices[19] = 1.0f;
    vertices[23] = 0.0f; vertices[24] = 1.0f;
    vertices[28] = 0.0f; vertices[29] = 0.0f;
    vertices[33] = 0.0f; vertices[34] = 0.0f;
    vertices[38] = 1.0f; vertices[39] = 0.0f;
    vertices[43] = 1.0f; vertices[44] = 1.0f;
    vertices[48] = 1.0f; vertices[49] = 1.0f;
    vertices[53] = 0.0f; vertices[54] = 1.0f;
    vertices[58] = 0.0f; vertices[59] = 0.0f;
    vertices[63] = 1.0f; vertices[64] = 0.0f;
    vertices[68] = 1.0f; vertices[69] = 1.0f;
    vertices[73] = 0.0f; vertices[74] = 1.0f;
    vertices[78] = 0.0f; vertices[79] = 1.0f;
    vertices[83] = 0.0f; vertices[84] = 0.0f;
    vertices[88] = 1.0f; vertices[89] = 0.0f;
    vertices[93] = 1.0f; vertices[94] = 0.0f;
    vertices[98] = 1.0f; vertices[99] = 1.0f;
    vertices[103] = 0.0f; vertices[104] = 1.0f;
    vertices[108] = 0.0f; vertices[109] = 1.0f;
    vertices[113] = 0.0f; vertices[114] = 0.0f;
    vertices[118] = 1.0f; vertices[119] = 0.0f;
    vertices[123] = 0.0f; vertices[124] = 1.0f;
    vertices[128] = 1.0f; vertices[129] = 1.0f;
    vertices[133] = 1.0f; vertices[134] = 0.0f;
    vertices[138] = 1.0f; vertices[139] = 0.0f;
    vertices[143] = 0.0f; vertices[144] = 0.0f;
    vertices[148] = 0.0f; vertices[149] = 1.0f;
    vertices[153] = 0.0f; vertices[154] = 1.0f;
    vertices[158] = 1.0f; vertices[159] = 1.0f;
    vertices[163] = 1.0f; vertices[164] = 0.0f;
    vertices[168] = 1.0f; vertices[169] = 0.0f;
    vertices[173] = 0.0f; vertices[174] = 0.0f;
    vertices[178] = 0.0f; vertices[179] = 1.0f;

    GLfloat a = _rozmiar_x/2;
    GLfloat b = _rozmiar_z/2;
    GLfloat c = _rozmiar_y/2;

    vertices[0]  = -a; vertices[1]  = -b; vertices[2]  = -c;
    vertices[5]  =  a; vertices[6]  = -b; vertices[7]  = -c;
    vertices[10] =  a; vertices[11] =  b; vertices[12] = -c;
    vertices[15] =  a; vertices[16] =  b; vertices[17] = -c;
    vertices[20] = -a; vertices[21] =  b; vertices[22] = -c;
    vertices[25] = -a; vertices[26] = -b; vertices[27] = -c;

    vertices[30] = -a; vertices[31] = -b; vertices[32] = c;
    vertices[35] =  a; vertices[36] = -b; vertices[37] = c;
    vertices[40] =  a; vertices[41] =  b; vertices[42] = c;
    vertices[45] =  a; vertices[46] =  b; vertices[47] = c;
    vertices[50] = -a; vertices[51] =  b; vertices[52] = c;
    vertices[55] = -a; vertices[56] = -b; vertices[57] = c;

    vertices[60] = -a; vertices[61] =  b; vertices[62] =  c;
    vertices[65] = -a; vertices[66] =  b; vertices[67] = -c;
    vertices[70] = -a; vertices[71] = -b; vertices[72] = -c;
    vertices[75] = -a; vertices[76] = -b; vertices[77] = -c;
    vertices[80] = -a; vertices[81] = -b; vertices[82] =  c;
    vertices[85] = -a; vertices[86] =  b; vertices[87] =  c;

    vertices[90]  = a; vertices[91]  =  b; vertices[92]  =  c;
    vertices[95]  = a; vertices[96]  =  b; vertices[97]  = -c;
    vertices[100] = a; vertices[101] = -b; vertices[102] = -c;
    vertices[105] = a; vertices[106] = -b; vertices[107] = -c;
    vertices[110] = a; vertices[111] = -b; vertices[112] =  c;
    vertices[115] = a; vertices[116] =  b; vertices[117] =  c;

    vertices[120] = -a; vertices[121] = -b; vertices[122] = -c;
    vertices[125] =  a; vertices[126] = -b; vertices[127] = -c;
    vertices[130] =  a; vertices[131] = -b; vertices[132] =  c;
    vertices[135] =  a; vertices[136] = -b; vertices[137] =  c;
    vertices[140] = -a; vertices[141] = -b; vertices[142] =  c;
    vertices[145] = -a; vertices[146] = -b; vertices[147] = -c;

    vertices[150] = -a; vertices[151] = b; vertices[152] = -c;
    vertices[155] =  a; vertices[156] = b; vertices[157] = -c;
    vertices[160] =  a; vertices[161] = b; vertices[162] =  c;
    vertices[165] =  a; vertices[166] = b; vertices[167] =  c;
    vertices[170] = -a; vertices[171] = b; vertices[172] =  c;
    vertices[175] = -a; vertices[176] = b; vertices[177] = -c;

    glGenVertexArrays(1, &this->_vao);
    glGenBuffers(1, &this->_vbo);
    glBindVertexArray(this->_vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);

    glGenTextures(1, &_tekstura);
    glBindTexture(GL_TEXTURE_2D, _tekstura);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int szerokosc, wysokosc;
    unsigned char* obraz = SOIL_load_image(tekstura_przeszkody, &szerokosc, &wysokosc, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, szerokosc, wysokosc, 0, GL_RGB, GL_UNSIGNED_BYTE, obraz);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(obraz);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void C_proste_ksztalty::rysuj(C_shader_loader shader_model, C_kamera_loader kamera_glowna){
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _tekstura);
    glUniform1i(glGetUniformLocation(shader_model._program, "ourTexture1"), 0);

    shader_model.uzyj_program();

    glm::mat4 rzutowanie = glm::perspective(kamera_glowna._przyblizenie,kamera_glowna._szerokosc/kamera_glowna._wysokosc,0.1f,100.0f);
    glUniformMatrix4fv(glGetUniformLocation(shader_model._program, "rzutowanie"), 1, GL_FALSE, glm::value_ptr(rzutowanie));

    glm::mat4 widok = kamera_glowna.macierz_lookAt();
    glUniformMatrix4fv(glGetUniformLocation(shader_model._program, "widok"), 1, GL_FALSE, glm::value_ptr(widok));

    glm::mat4 model;
    GLint modelLoc = glGetUniformLocation(shader_model._program, "model");
    model = glm::translate(model, glm::vec3(this->_pozycja_x, this->_pozycja_y, this->_pozycja_z));
    glUniformMatrix4fv( modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(this->_vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

C_opengl_window::C_opengl_window()
{
    this->inicjalizuj_C_opengl_framework();
    this->inicjalizuj_GL();
    this->obsluga_zdarzen();
}

C_opengl_window::~C_opengl_window(){
    delete _model_nanosuit;
    delete _model_dron;
    delete _model_podloga;
}

void C_opengl_window::start_GL(){
    while(!this->zamknieto_GLFW())
        this->obsluga_zdarzen();
}

void C_opengl_window::inicjalizuj_GL(){

    skyboxShader.wczytaj_z_pliku(shader_skybox_v,shader_skybox_f);
    _shader_model.wczytaj_z_pliku(shader_v,shader_f);
    skybox = new C_skybox;

    //_model_nanosuit = new C_model_loader(model_nanosuit);
    _model_dron = new C_model_loader(model_dron);
    _model_podloga = new C_model_loader(model_podloga);

}

void C_opengl_window::rysuj_GL(){
    std::string napis_ = pobierz_informacje_z_pamieci();

    if(napis_ != ""){
		if(napis_ == "koniec") { }

        std::cout << "odebrano: " << napis_ << std::endl;

        std::stringstream strumien;
        strumien << napis_;

        char srednik, zadanie;
        strumien >> zadanie >> srednik;

        std::string nazwa_przeszkody = "";
        GLfloat pozycja_x = 0;
        GLfloat pozycja_y = 0;
        GLfloat pozycja_z = 0;
        GLfloat rozmiar_x = 0;
        GLfloat rozmiar_y = 0;
        GLfloat rozmiar_z = 0;
		C_proste_ksztalty przeszkoda;

        switch(zadanie)
        {
            case 's':
                strumien >> x >> srednik >> y >> srednik >> z >> srednik >> pitch;
            break;

            case 'p':
                strumien >> pozycja_x >> srednik
						 >> pozycja_y >> srednik
						 >> pozycja_z >> srednik
						 >> rozmiar_x >> srednik
						 >> rozmiar_y >> srednik
						 >> rozmiar_z >> srednik
						 >> nazwa_przeszkody;

				przeszkoda.stworz(nazwa_przeszkody,pozycja_x,pozycja_y,pozycja_z,rozmiar_x,rozmiar_y,rozmiar_z);

                elementy_sceny.push_back(przeszkoda);
            break;

            default:
            break;
        }
    }

    skybox->rysuj(skyboxShader, _kamera_glowna);

    for(unsigned i=0;i<elementy_sceny.size();i++)
        elementy_sceny[i].rysuj(_shader_model,_kamera_glowna);

    //_model_nanosuit->rysuj(_shader_model,_kamera_glowna,x,y,z,yaw,-pitch,roll);
    _model_dron->rysuj(_shader_model,_kamera_glowna,x,y,z,yaw,pitch,roll);
    _model_podloga->rysuj(_shader_model,_kamera_glowna,0,-4.8,0,0,0,0);
}

std::string C_opengl_window::pobierz_informacje_z_pamieci(void){
    if (global_shared_mem->client_wrote) {
        global_shared_mem->client_wrote = 0;
        return global_shared_mem->text;
    }
    return "";
}
