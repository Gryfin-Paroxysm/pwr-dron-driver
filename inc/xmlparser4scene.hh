#ifndef XMLPARSER4SCENE_HH
#define XMLPARSER4SCENE_HH

#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/sax/Locator.hpp>
#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>

#include <map>
#include <string>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>

#ifndef XMLSize_t
#define XMLSize_t unsigned int
#endif

#include "scena.hh"

class XMLParser4Scene : public xercesc::DefaultHandler {

    C_scena  *_scena;

  public:
    XMLParser4Scene(C_scena &_scena);

    virtual void startElement(const XMLCh *const pURI, const XMLCh *const pLocalName, const XMLCh *const pQNname, const xercesc::Attributes& attrs);
    virtual void endElement(const XMLCh *const pURI, const XMLCh *const pLocalName, const XMLCh *const pQNname);

    void fatalError(const xercesc::SAXParseException&);
    void error(const xercesc::SAXParseException &exc);
    void warning(const xercesc::SAXParseException &exc);
    void WhenEndElement(const std::string& ElemName);
    void WhenStartElement( const std::string& ElemName, const xercesc::Attributes& Attrs );
};

#endif
