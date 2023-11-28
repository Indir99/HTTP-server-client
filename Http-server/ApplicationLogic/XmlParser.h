#pragma once

#include "XmlHandler.h"
#include <xercesc/framework/MemBufInputSource.hpp>
#include <memory>

namespace ApplicationLogic {

}
class XmlParser{
public:
    XmlParser() {
        m_handlerPtr = std::make_unique<XmlHandler>();
        m_parserPtr = std::unique_ptr<xercesc::SAX2XMLReader>(xercesc::XMLReaderFactory::createXMLReader());
        m_parserPtr->setContentHandler(m_handlerPtr.get());
        m_parserPtr->setErrorHandler(m_handlerPtr.get());
    }

    void ParseMessage(std::string_view message){
        // Create a MemBufInputSource from the string
        std::unique_ptr<xercesc::MemBufInputSource> inputSource(new xercesc::MemBufInputSource(
            reinterpret_cast<const XMLByte*>(message.data()), message.size(), "xmlData", false));
        m_parserPtr->parse(*inputSource);
    }

    static void ParseXmlMessage(std::string_view message) {
        XmlParser parser;
        parser.ParseMessage(message);
    }

    void PrintParsedElements(){
        std::cout<<" Parsred elements: "<<std::endl;
        for(const auto& element : m_handlerPtr->m_xmlElementsVector){
            std::cout<<"Element: "<< element.m_elementName<<", Value: "<< element.m_elementValue<<std::endl;
        }
    }

private:
    std::unique_ptr<XmlHandler> m_handlerPtr;
    std::unique_ptr<xercesc::SAX2XMLReader> m_parserPtr;
};
