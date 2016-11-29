#include "xmlparser4scene.hh"

/*!
 * Konstruktor klasy. Tutaj należy zainicjalizować wszystkie
 * dodatkowe pola.
 * (Ten opis należy odpowiednio uzupełnić)
 */
XMLParser4Scene::XMLParser4Scene(C_scena &scena){
    _scena = &scena;
}

/*!
 * Wykonuje operacje związane z wystąpieniem danego elementu XML.
 * W przypadku elementu \p "Action" będzie to utworzenie obiektu
 * reprezentującego odpowiednią działanie robota.
 * W przypadku elementu \p "Parameter" będzie to zapisanie parametrów
 * związanych z danym działaniem.
 * \param[in] ElemName -
 * \param[in] Attrs - (\b we,) atrybuty napotkanego elementu XML.
 */
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

/*!
 * Metoda jest wywoływana po napotkaniu nowego elementu XML, np.
 * gdy zostanie napotkany element:
   \verbatim
     <Action Name="Rotate">
   \endverbatim
 *  to poprzez parametr \e xscElemName jest dostęp do nazwy elementu
 *  tzn. \p Action,
 *  \param[in] pLocalName -  umożliwia dostęp do nazwy elementu XML.
 *                 W podanym przykładzie nazwą elementu XML jest "Action".
 *  \param[in] Attrs -  lista atrybutów danego symbolu XML.
 *                 W przykładzie pokazanym powyżej listę atrybutów
 *                 będą stanowiły napisy:
 */
void XMLParser4Scene::startElement(const XMLCh* const pURI, const XMLCh* const pLocalName, const XMLCh* const pQNname, const xercesc::Attributes& Attrs){
    char* sElemName = xercesc::XMLString::transcode(pLocalName);
    WhenStartElement(sElemName, Attrs);
    xercesc::XMLString::release(&sElemName);
}


/*!
 * Metoda zostaje wywołana w momencie zakończenia danego elementu
 * XML, np. jeżeli w pliku jest wpis:
   \verbatim
     <Action Name="Rotate">
     </Action>
   \endverbatim
 * to metoda ta zostanie wywołana po napotkaniu znacznika
 * \p </Action>. Jeżeli element XML ma formę skróconą, tzn.
   \verbatim
     <Parametr Name="Rotate"/>
   \endverbatim
 * to wówczas wywołana metoda wywołana zostanie w momencie
 * napotkania sekwencji "/>"
 *  \param[in] pLocalName -  umożliwia dostęp do nazwy elementu XML.
 *                 W podanym przykładzie nazwą elementu XML jest "Action".
 */
void XMLParser4Scene::endElement(const XMLCh* const pURI, const XMLCh* const pLocalName, const XMLCh* const pQName){
   char* sElemName = xercesc::XMLString::transcode(pLocalName);
   WhenEndElement(sElemName);
   xercesc::XMLString::release(&sElemName);
}

/*!
 * Wykonuje końcowe operacje związane z danym elementem XML.
 * W przypadku \p "Action" jest to dodanie utworzonego wcześniej
 * obiektu do listy poleceń robota.
 * Metoda wywoływana jest w momencie napotkania znacznika końca
 * danego elementu XML.
 * \param[in] ElemName -  nazwa elementu XML
 */
void XMLParser4Scene::WhenEndElement(const std::string& ElemName){
    if(ElemName == "Obstacle")
        _scena->_przeszkody.push_back(_scena->_nowa_przeszkoda);
}

/*!
 * Metoda wywoływana jest, gdy napotkany zostanie błąd fatalny,
 * np.
  \verbatim
    <Action Name="Rotate">
    </Parametr>
  \endverbatim
 */
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

/*!
 * Metoda jest wywoływana, gdy napotkany zostanie błąd, który nie
 * jest traktowany jako fatalny. W ten sposób traktowane są błędy
 * występujące w opisie gramatyki dokumentu.
 * \param[in] Except - zawiera informacje dotyczące błędu. Informacje
 *                     te to opis błędu oraz numer linii, w której
 *                     wystąpił błąd.
 */
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

/*!
 *
 */
void XMLParser4Scene::warning(const xercesc::SAXParseException&  Exception){
    std::cerr << "Ostrzezenie ..." << std::endl;
}
