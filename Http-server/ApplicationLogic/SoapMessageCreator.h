#pragma once

#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <string>




namespace ApplicationLogic{

constexpr char ThisDeviceAddress[]{"http://127.0.0.1:xxxxx"};
constexpr char ThisDeviceName[]{"MedicalServerTypeA"};

constexpr char SoapNameSpaceUri[]{"http://soap-example.com/namespace"};
constexpr char WsAddressingUri[]{"http://wsaddressing-example.com/namespace"};
constexpr char BodyUri[]{"http://med-body/example.com/namespace"};
constexpr char SoapEnvelopeName[]{"soap:Envelope"};
constexpr char SoapHeaderName[]{"soap:Header"};
constexpr char SoapBodyName[]{"soap:Body"};
constexpr char AddressName[]{"ws-addr:Address"};
constexpr char ToName[]{"ws-addr:To"};

constexpr char setOneResponse[]{"Set command type ONE executed successfully. Database successfully updated."};
constexpr char setTwoResponse[]{"Set command type TWO executed successfully. Database successfully updated."};


void InitializeLibrary();       // Done
void DeinitializeLibrary();     // Done

std::string PrepareHelloMessage();                  // Done
std::string PrepareServerAcceptMessage();           // Done
std::string PrepareServerDenyMessage();             // Done
std::string PrepareProbeMatchMessage();             // Done
std::string PrepareGetDataBaseResponseMessage();    // Done
std::string PrepareSubscribeResponseMessage();      // Done
std::string PrepareUnsubscribeResponseMessage();    // Done
std::string PrepareReportTypeAmessage(std::string patientID,
                                      std::string patientFirstName,
                                      std::string patientLastName,
                                      std::string bloodPressure,
                                      std::string temperature,
                                      std::string heartRate);
std::string PrepareReportTypeBmessage(std::string patientID,
                                      std::string patientFirstName,
                                      std::string patientLastName,
                                      std::string doctorID,
                                      std::string doctorFirstName,
                                      std::string doctorLastName,
                                      std::string therapyName,
                                      std::string therapyStatus);
std::string PrepareStoppingReportsMessage();        // Done
std::string PrepareSetCommandOneResponseMessage();  // TODO
std::string PrepareSetCommandTwoResponseMessage();  // TODO

} // ApplicationLogic
