#pragma once

#include "XmlHandler.h"
#include "XmlStructures.h"
#include "SoapMessageCreator.h"
#include <xercesc/framework/MemBufInputSource.hpp>
#include <memory>

namespace ApplicationLogic {

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
    template<typename T>
    void GetHeaderData(T& data){
        for(const auto& element : m_handlerPtr->m_xmlElementsVector){
            if(element.m_elementName == AddressName){
                data.header.senderAddress = element.m_elementValue;
            }
            else if(element.m_elementName == ToName) {
                data.header.receiverAddress = element.m_elementValue;
            }
        }
    }
    void GetProbeData(ProbeData& probe){
        GetHeaderData(probe);
        for(const auto& element : m_handlerPtr->m_xmlElementsVector) {
            if(element.m_elementName == "mb:Type") {
                probe.deviceName = element.m_elementValue;
            }
        }
    }
    void GetDataBaseData(DatabaseData& database){
        GetHeaderData(database);
        for(const auto& element : m_handlerPtr->m_xmlElementsVector) {
            if(element.m_elementName == "mb:DataBase") {
                database.databaseText = element.m_elementValue;
            }
        }
    }
    void GetSubscribeData(SubscribeData& subscr){
        GetHeaderData(subscr);
        for(const auto& element : m_handlerPtr->m_xmlElementsVector) {
            if(element.m_elementName == "mb:SubscribeElements") {
                subscr.listOfReports = element.m_elementValue;
            }
        }
    }
    void GetStartReportsData(StartReportsData& data) {
        GetHeaderData(data);
        for(const auto& element : m_handlerPtr->m_xmlElementsVector) {
            if(element.m_elementName == "mb:StartReports") {
                data.command = element.m_elementValue;
            }
        }
    }
    void ReportTypeAresponseData(ReportTypeAdata& aData){
        GetHeaderData(aData);
        for(const auto& element : m_handlerPtr->m_xmlElementsVector) {
            if(element.m_elementName == "mb:ReportTypeAResponse") {
                aData.responseText = element.m_elementValue;
            }
        }
    }

    void ReportTypeBresponseData(ReportTypeBdata& aData){
        GetHeaderData(aData);
        for(const auto& element : m_handlerPtr->m_xmlElementsVector) {
            if(element.m_elementName == "mb:ReportTypeBResponse") {
                aData.responseText = element.m_elementValue;
            }
        }
    }

    void GetCommandOneData(SetCommandOneData& data){
        GetHeaderData(data);
        for(const auto& element : m_handlerPtr->m_xmlElementsVector) {
            if(element.m_elementName == "mb:PatientID") {
                data.patiendID = element.m_elementValue;
            } else if (element.m_elementName == "mb:Operation") {
                data.operation = element.m_elementValue;
            } else if(element.m_elementName == "mb:CurrentTime") {
                data.time = element.m_elementValue;
            }
        }
    }
    void GetCommandTwoData(SetCommandTwoData& data){
        GetHeaderData(data);
        for(const auto& element : m_handlerPtr->m_xmlElementsVector) {
            if(element.m_elementName == "mb:PatientID") {
                data.patiendID = element.m_elementValue;
            } else if (element.m_elementName == "mb:Operation") {
                data.operation = element.m_elementValue;
            } else if(element.m_elementName == "mb:OperationValue") {
                data.opValue = element.m_elementValue;
            } else if(element.m_elementName == "mb:CurrentTime") {
                data.time = element.m_elementValue;
            }
        }
    }

private:
    std::unique_ptr<XmlHandler> m_handlerPtr;
    std::unique_ptr<xercesc::SAX2XMLReader> m_parserPtr;
};

} // ApplicationLogic
