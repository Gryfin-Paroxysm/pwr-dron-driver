#include "xmlparser4scene.hh"

XMLParser4Scene::XMLParser4Scene(C_scena &scena){
    _scena = &scena;
}

void XMLParser4Scene::WhenStartElement(const std::string &ElemName, const xercesc::Attributes &Attrs){
    unsigned i = 0;

    if(ElemName == "Scene") return;

    else if(ElemName == "Obstacle"){
        _scena->_nowa_przeszkoda._nazwa_przeszkody = xercesc::XMLString::transcode(Attrs.getValue(i));
    }

    else if(ElemName == "Parameter"){
        char* wartosc_atrybutu_0 = xercesc::XMLString::transcode(Attrs.getValue(i));
        char* wartosc_atrybutu_1 = xercesc::XMLString::transcode(Attrs.getValue(i+1));

        std::stringstream strumien;
        strumien << wartosc_atrybutu_1;

        if((std::string)wartosc_atrybutu_0 == "Center_x")
            strumien >> _scena->_nowa_przeszkoda._pozycja._x;
        else if((std::string)wartosc_atrybutu_0 == "Center_y")
            strumien >> _scena->_nowa_przeszkoda._pozycja._y;
        else if((std::string)wartosc_atrybutu_0 == "Center_z")
            strumien >> _scena->_nowa_przeszkoda._pozycja._z;
        else if((std::string)wartosc_atrybutu_0 == "Size_x")
            strumien >> _scena->_nowa_przeszkoda._rozmiar._x;
        else if((std::string)wartosc_atrybutu_0 == "Size_y")
            strumien >> _scena->_nowa_przeszkoda._rozmiar._y;
        else if((std::string)wartosc_atrybutu_0 == "Size_z")
            strumien >> _scena->_nowa_przeszkoda._rozmiar._z;
    }
}

void XMLParser4Scene::startElement(const XMLCh* const pURI, const XMLCh* const pLocalName, const XMLCh* const pQNname, const xercesc::Attributes& Attrs){
    char* sElemName = xercesc::XMLString::transcode(pLocalName);
    WhenStartElement(sElemName, Attrs);
    xercesc::XMLString::release(&sElemName);
}

void XMLParser4Scene::endElement(const XMLCh* const pURI, const XMLCh* const pLocalName, const XMLCh* const pQName){
   char* sElemName = xercesc::XMLString::transcode(pLocalName);
   WhenEndElement(sElemName);
   xercesc::XMLString::release(&sElemName);
}

void XMLParser4Scene::WhenEndElement(const std::string& ElemName){
    if(ElemName == "Obstacle")
        _scena->_przeszkody.push_back(_scena->_nowa_przeszkoda);
}

void XMLParser4Scene::fatalError(const xercesc::SAXParseException& Exception){
    char* sMessage = xercesc::XMLString::transcode(Exception.getMessage());
    char* sSystemId = xercesc::XMLString::transcode(Exception.getSystemId());

    std::cerr << "Blad fatalny! " << std::endl
              << "    Plik:  " << sSystemId << std::endl
              << "   Linia: " << Exception.getLineNumber() << std::endl
              << " Kolumna: " << Exception.getColumnNumber() << std::endl
              << " Informacja: " << sMessage << std::endl;

    xercesc::XMLString::release(&sMessage);
    xercesc::XMLString::release(&sSystemId);
}

void XMLParser4Scene::error(const xercesc::SAXParseException& Exception){
    std::cerr << "Blad ..." << std::endl;
    char* sMessage = xercesc::XMLString::transcode(Exception.getMessage());
    char* sSystemId = xercesc::XMLString::transcode(Exception.getSystemId());

    std::cerr << "Blad fatalny! " << std::endl
              << "    Plik:  " << sSystemId << std::endl
              << "   Linia: " << Exception.getLineNumber() << std::endl
              << " Kolumna: " << Exception.getColumnNumber() << std::endl
              << " Informacja: " << sMessage << std::endl;

    xercesc::XMLString::release(&sMessage);
    xercesc::XMLString::release(&sSystemId);
}

void XMLParser4Scene::warning(const xercesc::SAXParseException&  Exception){
    std::cerr << "Ostrzezenie ..." << std::endl;
}
