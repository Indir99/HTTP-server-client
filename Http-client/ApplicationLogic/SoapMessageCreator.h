#pragma once

#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <string>


namespace ApplicationLogic{

constexpr char ThisDeviceAddress[]{"http://127.0.0.1:xxxxx"};
constexpr char ThisDeviceName[]{"MedicalDeviceTypeA"};

constexpr char SoapNameSpaceUri[]{"http://soap-example.com/namespace"};
constexpr char WsAddressingUri[]{"http://wsaddressing-example.com/namespace"};
constexpr char BodyUri[]{"http://med-body/example.com/namespace"};
constexpr char SoapEnvelopeName[]{"soap:Envelope"};
constexpr char SoapHeaderName[]{"soap:Header"};
constexpr char SoapBodyName[]{"soap:Body"};
constexpr char AddressName[]{"ws-addr:Address"};
constexpr char ToName[]{"ws-addr:To"};
constexpr char reportAresponse[]{"Report type A was successfully received and the database was successfully updated."};
constexpr char reportBresponse[]{"Report type B was successfully received and the database was successfully updated."};

void InitializeLibrary();       // Done
void DeinitializeLibrary();     // Done

std::string PrepareHelloMessage();                  // Done
std::string PrepareProbeMessage();                  // Done
std::string PrepareGetDataBaseMessage();            // Done
std::string PrepareSubscribeMessage();              // Done
std::string PrepareUnsubscribeMessage();            // Done
std::string PrepareReportTypeAresponseMessage();    // Done
std::string PrepareReportTypeBresponseMessage();    // Done
std::string PrepareSetCommandOneMessage(std::string patientID,
                                        std::string operation);
std::string PrepareSetCommandTwoMessage(std::string patientID,
                                        std::string operation,
                                        std::string value);
std::string PrepareGracefullyDisconnectMessage();   // Done
std::string PrepareStartReports();                  // Done

} // ApplicationLogic
