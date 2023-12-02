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
    void GetProbeMatchData(ProbeMatchData& probe){
        GetHeaderData(probe);
        for(const auto& element : m_handlerPtr->m_xmlElementsVector) {
            if(element.m_elementName == "mb:Type") {
                probe.deviceName = element.m_elementValue;
            }
        }
    }
    void GetDataBaseResponseData(DatabaseResponseData& database){
        GetHeaderData(database);
        for(const auto& element : m_handlerPtr->m_xmlElementsVector) {
            if(element.m_elementName == "mb:Patient") {
                database.patientText = element.m_elementValue;
            } else if(element.m_elementName == "mb:Doctor") {
                database.doctorText = element.m_elementValue;
            } else if(element.m_elementName == "mb:Therapy") {
                database.therapyText = element.m_elementValue;
            }
        }
    }
    void GetSubscribeResponseData(SubscribResponseData& subscr){
        GetHeaderData(subscr);
        for(const auto& element : m_handlerPtr->m_xmlElementsVector) {
            if(element.m_elementName == "mb:SubscribedElements") {
                subscr.listOfReports = element.m_elementValue;
            }
        }
    }
    void GetStoppingReportsData(StoppingReportsData& data) {
        GetHeaderData(data);
        for(const auto& element : m_handlerPtr->m_xmlElementsVector) {
            if(element.m_elementName == "mb:StopReports") {
                data.command = element.m_elementValue;
            }
        }
    }

    void GetReportTypeAdata(ReportTypeAdata& data){
        GetHeaderData(data);
        for(const auto& element : m_handlerPtr->m_xmlElementsVector) {
            if(element.m_elementName == "mb:PatientID") {
                data.patientID = element.m_elementValue;
            } else if(element.m_elementName == "mb:PatientFirstName") {
                data.patientFirstName = element.m_elementValue;
            } else if(element.m_elementName == "mb:PatientLastName") {
                data.patientLastName = element.m_elementValue;
            } else if(element.m_elementName == "mb:PatientBloodPressure") {
                data.bloodPressure = element.m_elementValue;
            } else if(element.m_elementName == "mb:PatientTemperature") {
                data.temperature = element.m_elementValue;
            } else if(element.m_elementName == "mb:PatientHeartRate") {
                data.heartRate = element.m_elementValue;
            } else if(element.m_elementName == "mb:CurrentTime") {
                data.time = element.m_elementValue;
            }
        }
    }

    void GetReportTypeBdata(ReportTypeBdata& data){
        GetHeaderData(data);
        for(const auto& element : m_handlerPtr->m_xmlElementsVector) {
            if(element.m_elementName == "mb:PatientID") {
                data.patientID = element.m_elementValue;
            } else if(element.m_elementName == "mb:PatientFirstName") {
                data.patientFirstName = element.m_elementValue;
            } else if(element.m_elementName == "mb:PatientLastName") {
                data.patientLastName = element.m_elementValue;
            } else if(element.m_elementName == "mb:DoctorID") {
                data.doctorID = element.m_elementValue;
            } else if(element.m_elementName == "mb:DoctorFirstName") {
                data.doctorFirstName = element.m_elementValue;
            } else if(element.m_elementName == "mb:DoctorLastName") {
                data.doctortLastName = element.m_elementValue;
            } else if(element.m_elementName == "mb:CurrentTime") {
                data.time = element.m_elementValue;
            } else if(element.m_elementName == "mb:TherapyName") {
                data.therapyName = element.m_elementValue;
            } else if(element.m_elementName == "mb:TherapyStatus") {
                data.therapyStatus = element.m_elementValue;
            }
        }
    }

    void GetCommandOneResponseData(SetCommandOneResponseData& data){
        GetHeaderData(data);
        for(const auto& element : m_handlerPtr->m_xmlElementsVector) {
            if(element.m_elementName == "mb:SetCommandOneResponse") {
                data.responseText = element.m_elementValue;
            }
        }
    }

    void GetCommandTwoResponseData(SetCommandTwoResponseData& data){
        GetHeaderData(data);
        for(const auto& element : m_handlerPtr->m_xmlElementsVector) {
            if(element.m_elementName == "mb:SetCommandTwoResponse") {
                data.responseText = element.m_elementValue;
            }
        }
    }

private:
    std::unique_ptr<XmlHandler> m_handlerPtr;
    std::unique_ptr<xercesc::SAX2XMLReader> m_parserPtr;
};

} // ApplicationLogic
