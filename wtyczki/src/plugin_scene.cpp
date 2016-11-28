#include "plugin_scene.hh"

void C_scene::wyswietl_komende() const{
    std::cout << zwroc_nazwe_komendy() << " " << _nazwa_dokumentu_xml << std::endl;
}

void C_scene::wyswietl_skladnie_komendy() const{
    std::cout << "   ReadScene  nazwa_dokumentu [xml]" << std::endl;
}

const char* C_scene::zwroc_nazwe_komendy() const{
    return "ReadScene";
}

bool C_scene::odczytaj_plik_xml(const char* plik_z_gramatyka, const char* plik_xml, C_scena& scena) const{
    try{
        xercesc::XMLPlatformUtils::Initialize();
    }
    catch (const xercesc::XMLException& toCatch){
        char* message = xercesc::XMLString::transcode(toCatch.getMessage());
        std::cerr << "Error during initialization! :\n";
        std::cerr << "Exception message is: \n" << message << "\n";
        xercesc::XMLString::release(&message);
        return false;
    }

    xercesc::SAX2XMLReader* pParser = xercesc::XMLReaderFactory::createXMLReader();
    pParser->setFeature(xercesc::XMLUni::fgSAX2CoreNameSpaces, true);
    pParser->setFeature(xercesc::XMLUni::fgSAX2CoreValidation, true);
    pParser->setFeature(xercesc::XMLUni::fgXercesDynamic, false);
    pParser->setFeature(xercesc::XMLUni::fgXercesSchema, true);
    pParser->setFeature(xercesc::XMLUni::fgXercesSchemaFullChecking, true);

    pParser->setFeature(xercesc::XMLUni::fgXercesValidationErrorAsFatal, true);

    xercesc::DefaultHandler* pHandler = new XMLParser4Scene(scena);
    pParser->setContentHandler(pHandler);
    pParser->setErrorHandler(pHandler);

    try {
        if (!pParser->loadGrammar(plik_z_gramatyka, xercesc::Grammar::SchemaGrammarType,true)){
            std::cerr << "!!! " << plik_z_gramatyka << ", '" << std::endl
                      << "!!! ktory zawiera opis gramatyki, nie moze zostac wczytany." << std::endl;
            return false;
        }
        pParser->setFeature(xercesc::XMLUni::fgXercesUseCachedGrammarInParse,true);
        pParser->parse(plik_xml);
    }
    catch (const xercesc::XMLException& Exception){
        char* sMessage = xercesc::XMLString::transcode(Exception.getMessage());
        std::cerr << "Informacja o wyjatku: \n" << "   " << sMessage << "\n";
        xercesc::XMLString::release(&sMessage);
        return false;
    }
    catch (const xercesc::SAXParseException& Exception){
        char* sMessage = xercesc::XMLString::transcode(Exception.getMessage());
        char* sSystemId = xercesc::XMLString::transcode(Exception.getSystemId());

        std::cerr << "Blad! " << std::endl
                  << "    Plik:  " << sSystemId << std::endl
                  << "   Linia: " << Exception.getLineNumber() << std::endl
                  << " Kolumna: " << Exception.getColumnNumber() << std::endl
                  << " Informacja: " << sMessage
                  << std::endl;

        xercesc::XMLString::release(&sMessage);
        xercesc::XMLString::release(&sSystemId);
        return false;
    }
    catch(...){
        std::cout << "Zgloszony zostal nieoczekiwany wyjatek!\n" ;
        return false;
    }

    delete pParser;
    delete pHandler;
    return true;
}

bool C_scene::wykonaj_komende(C_dron *dron) const{
    if (!odczytaj_plik_xml("xml/grammar/scene.xsd",_nazwa_dokumentu_xml.c_str(),dron->_scena))
        return false;
    wyslij_informacje_do_wizualizacji(dron);
    return true;
}

void C_scene::wyslij_informacje_do_wizualizacji(C_dron *dron) const{
    for(unsigned i=0;i<dron->_scena._przeszkody.size();i++){
        std::stringstream strumien_informacji;
        strumien_informacji << 'p' << ';';
        strumien_informacji << dron->_scena._przeszkody[i]._nazwa_przeszkody << ';';
        strumien_informacji << dron->_scena._przeszkody[i]._pozycja._x << ';';
        strumien_informacji << dron->_scena._przeszkody[i]._pozycja._y << ';';
        strumien_informacji << dron->_scena._przeszkody[i]._pozycja._z << ';';
        strumien_informacji << dron->_scena._przeszkody[i]._rozmiar._x << ';';
        strumien_informacji << dron->_scena._przeszkody[i]._rozmiar._y << ';';
        strumien_informacji << dron->_scena._przeszkody[i]._rozmiar._z;
        std::string informacja = strumien_informacji.str();
        dron->przekaz_informacje_do_pamieci(informacja);
        /*trzeba poczekać aż informacje zostaną przekazane, to rozwiązanie jest nieprawidłowe, ale na inne nie ma czasu*/
        /*proponuje się tu zrobić mutex*/
        sleep(1);
    }
}

bool C_scene::odczytaj_komende(std::istream& strumien_komendy){
    strumien_komendy >> _nazwa_dokumentu_xml;
    if(strumien_komendy.fail())
        return false;
    return true;
}

extern "C" C_plugin* stworz(){
    return new C_scene;
}

extern "C" void usun(C_plugin* objekt){
    delete objekt;
}
