#include "model_loader.hh"

C_bryla::C_bryla(std::vector<wierzcholek> wierzcholki, std::vector<GLuint> polaczenia, std::vector<tekstura> tekstury){
    this->_wierzcholki = wierzcholki;
    this->_polaczenia = polaczenia;
    this->_tekstury = tekstury;

    this->inicjalizuj_bryle();
}

void C_bryla::rysuj(C_shader_loader shader_modelu, C_kamera_loader kamera_glowna, GLfloat x, GLfloat y, GLfloat z, GLfloat ya, GLfloat pi, GLfloat ro){
    shader_modelu.uzyj_program();

    glm::mat4 rzutowanie = glm::perspective(kamera_glowna._przyblizenie,kamera_glowna._szerokosc/kamera_glowna._wysokosc,0.1f,100.0f);
    glUniformMatrix4fv(glGetUniformLocation(shader_modelu._program, "rzutowanie"), 1, GL_FALSE, glm::value_ptr(rzutowanie));

    glm::mat4 widok = kamera_glowna.macierz_lookAt();
    glUniformMatrix4fv(glGetUniformLocation(shader_modelu._program, "widok"), 1, GL_FALSE, glm::value_ptr(widok));

    GLuint diffuse_iterator = 1;
    GLuint specular_iterator = 1;

    for(GLuint i = 0; i < this->_tekstury.size(); i++){
        glActiveTexture(GL_TEXTURE0 + i);
        std::stringstream strumien;
        std::string nazwa = this->_tekstury[i]._typ;
        if(nazwa == "texture_diffuse")       strumien << diffuse_iterator++;
        else if(nazwa == "texture_specular") strumien << specular_iterator++;
        std::string numer = strumien.str();
        glUniform1i(glGetUniformLocation(shader_modelu._program, (nazwa + numer).c_str()), i);
        glBindTexture(GL_TEXTURE_2D, this->_tekstury[i]._id);
    }

    glUniform1f(glGetUniformLocation(shader_modelu._program, "material.shininess"), 16.0f);

    glm::mat4 model;
    GLint modelLoc = glGetUniformLocation(shader_modelu._program, "model");
    model = glm::translate(model, glm::vec3( x, y, z));
    model = glm::rotate(model, glm::radians(ya), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(pi), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(ro), glm::vec3(0.0f, 0.0f, 1.0f));
    glUniformMatrix4fv( modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(this->_vao);
    glDrawElements(GL_TRIANGLES, this->_polaczenia.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    for (GLuint i = 0; i < this->_tekstury.size(); i++){
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void C_bryla::inicjalizuj_bryle(){
    glGenVertexArrays(1, &this->_vao);
    glGenBuffers(1, &this->_vbo);
    glGenBuffers(1, &this->_ebo);

    glBindVertexArray(this->_vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);
    glBufferData(GL_ARRAY_BUFFER, this->_wierzcholki.size() * sizeof(wierzcholek), &this->_wierzcholki[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->_polaczenia.size() * sizeof(GLuint), &this->_polaczenia[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(wierzcholek), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(wierzcholek), (GLvoid*)offsetof(wierzcholek, _normalne));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(wierzcholek), (GLvoid*)offsetof(wierzcholek, _koordynaty_tekstury));
    glBindVertexArray(0);
}

C_model_loader::C_model_loader(const char* sciezka){
    this->wczytaj_model(sciezka);
}

void C_model_loader::rysuj(C_shader_loader shader_modelu, C_kamera_loader kamera_glowna, GLfloat x, GLfloat y, GLfloat z, GLfloat ya, GLfloat pi, GLfloat ro){
    for(GLuint i = 0; i < this->_bryly.size(); i++)
        this->_bryly[i].rysuj(shader_modelu,kamera_glowna,x,y,z,ya,pi,ro);
}

void C_model_loader::wczytaj_model(std::string sciezka){
    Assimp::Importer importer;

    const aiScene* scena = importer.ReadFile(sciezka, aiProcess_Triangulate | aiProcess_FlipUVs);
    if(!scena || scena->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scena->mRootNode){
        std::cerr << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }

    this->_folder = sciezka.substr(0, sciezka.find_last_of('/'));
    this->przeszukaj_wezly(scena->mRootNode, scena);
}

void C_model_loader::przeszukaj_wezly(aiNode* wezel, const aiScene* scena){
    for(GLuint i = 0; i < wezel->mNumMeshes; i++){
        aiMesh* bryla = scena->mMeshes[wezel->mMeshes[i]];
        this->_bryly.push_back(this->wczytaj_bryle(bryla, scena));
    }

    for(GLuint i = 0; i < wezel->mNumChildren; i++)
        this->przeszukaj_wezly(wezel->mChildren[i], scena);
}

C_bryla C_model_loader::wczytaj_bryle(aiMesh* bryla, const aiScene* scena){
    std::vector<wierzcholek> wierzcholki;
    std::vector<GLuint> polaczenia;
    std::vector<tekstura> tekstury;

    for(GLuint i = 0; i < bryla->mNumVertices; i++){
        wierzcholek wierzcholek_;

        wierzcholek_._wspolrzedne = glm::vec3(bryla->mVertices[i].x,bryla->mVertices[i].y,bryla->mVertices[i].z);
        wierzcholek_._normalne = glm::vec3(bryla->mNormals[i].x,bryla->mNormals[i].y,bryla->mNormals[i].z);

        if(bryla->mTextureCoords[0])
            wierzcholek_._koordynaty_tekstury = glm::vec2(bryla->mTextureCoords[0][i].x,bryla->mTextureCoords[0][i].y);
        else
            wierzcholek_._koordynaty_tekstury = glm::vec2(0.0f, 0.0f);

        wierzcholki.push_back(wierzcholek_);
    }

    for(GLuint i = 0; i < bryla->mNumFaces; i++){
        aiFace sciana = bryla->mFaces[i];
        for(GLuint j = 0; j < sciana.mNumIndices; j++)
            polaczenia.push_back(sciana.mIndices[j]);
    }

    if(bryla->mMaterialIndex >= 0){
        aiMaterial* material = scena->mMaterials[bryla->mMaterialIndex];

        std::vector<tekstura> diffuse_map = this->wczytaj_material(material, aiTextureType_DIFFUSE, "texture_diffuse");
        tekstury.insert(tekstury.end(), diffuse_map.begin(), diffuse_map.end());

        std::vector<tekstura> specular_map = this->wczytaj_material(material, aiTextureType_SPECULAR, "texture_specular");
        tekstury.insert(tekstury.end(), specular_map.begin(), specular_map.end());
    }

    return C_bryla(wierzcholki, polaczenia, tekstury);
}

std::vector<tekstura> C_model_loader::wczytaj_material(aiMaterial* material, aiTextureType typ, std::string nazwa_typu){
    std::vector<tekstura> tekstury;
    for(GLuint i = 0; i < material->GetTextureCount(typ); i++)
    {
        aiString sciezka;
        material->GetTexture(typ, i, &sciezka);

        GLboolean flaga_pominiecia = false;
        for(GLuint j = 0; j < _tekstury_wczytane.size(); j++)
        {
            if(_tekstury_wczytane[j]._sciezka == sciezka)
            {
                tekstury.push_back(_tekstury_wczytane[j]);
                flaga_pominiecia = true;
                break;
            }
        }
        if(!flaga_pominiecia)
        {
            tekstura tekstura_;
            tekstura_._id = wczytaj_teksture_z_pliku(sciezka.C_Str(), this->_folder);
            tekstura_._typ = nazwa_typu;
            tekstura_._sciezka = sciezka;
            tekstury.push_back(tekstura_);
            this->_tekstury_wczytane.push_back(tekstura_);
        }
    }
    return tekstury;
}

GLint C_model_loader::wczytaj_teksture_z_pliku(const char* sciezka, std::string folder){
    std::string nazwa_pliku = std::string(sciezka);
    nazwa_pliku = folder + '/' + nazwa_pliku;
    GLuint id_tekstury;
    glGenTextures(1, &id_tekstury);

    int szerokosc;
    int wysokosc;
    unsigned char* obraz = SOIL_load_image(nazwa_pliku.c_str(), &szerokosc, &wysokosc, 0, SOIL_LOAD_RGB);

    glBindTexture(GL_TEXTURE_2D, id_tekstury);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, szerokosc, wysokosc, 0, GL_RGB, GL_UNSIGNED_BYTE, obraz);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    SOIL_free_image_data(obraz);
    return id_tekstury;
}
