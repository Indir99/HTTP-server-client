#pragma once

#include <iostream>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/sax2/Attributes.hpp>
#include <vector>

namespace ApplicationLogic {

class XmlHandler : public xercesc::DefaultHandler {

private:
    struct XmlElementInfo{
        template<typename ElementName_TYPE, typename ElementValue_Type>
        XmlElementInfo(ElementName_TYPE&& name, ElementValue_Type&& value) :
            m_elementName{std::forward<ElementName_TYPE>(name)},
            m_elementValue{std::forward<ElementValue_Type>(value)}{
        }
        std::string m_elementName;
        std::string m_elementValue;
    };


    // Overriding startElement and endElement to handle XML elements
    void startElement(const XMLCh* const uri, const XMLCh* const localName,
                      const XMLCh* const qname, const xercesc::Attributes& attrs) override {
        // Convert XMLCh strings to char strings for printing
        char* uriStr = xercesc::XMLString::transcode(uri);
        char* localNameStr = xercesc::XMLString::transcode(localName);
        char* qnameStr = xercesc::XMLString::transcode(qname);

        //std::cout << "Start Element: " << qnameStr << std::endl;
        m_currentElement = qnameStr;

        // Print attributes, if any
        for (XMLSize_t i = 0; i < attrs.getLength(); ++i) {
            char* attrName = xercesc::XMLString::transcode(attrs.getLocalName(i));
            char* attrValue = xercesc::XMLString::transcode(attrs.getValue(i));
            //std::cout << "  Attribute: " << attrName << " = " << attrValue << std::endl;
            xercesc::XMLString::release(&attrName);
            xercesc::XMLString::release(&attrValue);
        }

        // Release memory
        xercesc::XMLString::release(&uriStr);
        xercesc::XMLString::release(&localNameStr);
        xercesc::XMLString::release(&qnameStr);
    }

    void endElement(const XMLCh* const uri, const XMLCh* const localName,
                    const XMLCh* const qname) override {
        char* uriStr = xercesc::XMLString::transcode(uri);
        char* localNameStr = xercesc::XMLString::transcode(localName);
        char* qnameStr = xercesc::XMLString::transcode(qname);

        //std::cout << "End Element: " << qnameStr << std::endl;

        xercesc::XMLString::release(&uriStr);
        xercesc::XMLString::release(&localNameStr);
        xercesc::XMLString::release(&qnameStr);
    }

    // Override characters() to handle character data
    void characters(const XMLCh* const chars, const XMLSize_t length) override {
        char* charData = xercesc::XMLString::transcode(chars);
        //std::cout << "Character Data: " << charData << std::endl;
        m_currentValue = charData;
        m_xmlElementsVector.emplace_back(std::move(m_currentElement), std::move(m_currentValue));
        xercesc::XMLString::release(&charData);
    }
public:
    std::vector<XmlElementInfo> m_xmlElementsVector;
    std::string m_currentElement;
    std::string m_currentValue;
};

} // ApplicationLogic
