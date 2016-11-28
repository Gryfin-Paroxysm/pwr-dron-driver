#ifndef SCENE_HH
#define SCENE_HH

#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>

#include <iostream>
#include <list>

#include "xmlparser4scene.hh"
#include "plugin.hh"


class C_scene: public C_plugin {

	std::string _nazwa_dokumentu_xml;

  public:

    virtual void wyswietl_komende() const;
    virtual void wyswietl_skladnie_komendy() const;
    virtual const char* zwroc_nazwe_komendy() const;
    virtual bool wykonaj_komende(C_dron *dron) const;
    virtual bool odczytaj_komende(std::istream& strumien_komendy);

    static C_plugin* stworz();
    static void usun(C_plugin* objekt);

  private:

    bool odczytaj_plik_xml(const char* plik_z_gramatyka, const char* plik_xml, C_scena& scena) const;
    void wyslij_informacje_do_wizualizacji(C_dron *dron) const;

};

#endif /// SCENE_HH

