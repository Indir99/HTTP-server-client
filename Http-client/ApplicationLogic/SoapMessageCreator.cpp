#include "SoapMessageCreator.h"
#include <chrono>

namespace ApplicationLogic {


namespace {


// supported tpyes
// MedicalDeviceTypeA
// MedicalDeciveTypeB
// supported types
// MedicalServerTypeA
// MedicalServerTypeB

}

void InitializeLibrary(){
    xercesc::XMLPlatformUtils::Initialize();
}

void DeinitializeLibrary(){
    xercesc::XMLPlatformUtils::Terminate();
}

std::string PrepareHelloMessage(){
    return "Hello from Medical-Device";
}


std::string PrepareProbeMessage(){
    // Get the implementation of the DOM
    xercesc::DOMImplementation* domImplementation = xercesc::DOMImplementationRegistry::getDOMImplementation(xercesc::XMLString::transcode("Core"));

    // Create a DOM document
    xercesc::DOMDocument* xmlDoc = domImplementation->createDocument(xercesc::XMLString::transcode(SoapNameSpaceUri),
                                                                     xercesc::XMLString::transcode(SoapEnvelopeName),
                                                                     0);
    // Get the root element
    xercesc::DOMElement* Envelope = xmlDoc->getDocumentElement();

    // Crate Header
    xercesc::DOMElement* Header = xmlDoc->createElementNS(xercesc::XMLString::transcode(SoapNameSpaceUri),
                                                          xercesc::XMLString::transcode(SoapHeaderName));
    Envelope->appendChild(Header);

    xercesc::DOMElement* HeaderAddress = xmlDoc->createElementNS(xercesc::XMLString::transcode(WsAddressingUri),
                                                          xercesc::XMLString::transcode(AddressName));
    Header->appendChild(HeaderAddress);

    xercesc::DOMText* addressText = xmlDoc->createTextNode(xercesc::XMLString::transcode(ThisDeviceAddress));
    HeaderAddress->appendChild(addressText);

    xercesc::DOMElement* HeaderTo = xmlDoc->createElementNS(xercesc::XMLString::transcode(WsAddressingUri),
                                                                 xercesc::XMLString::transcode(ToName));
    Header->appendChild(HeaderTo);

    xercesc::DOMText* toText = xmlDoc->createTextNode(xercesc::XMLString::transcode(ThisDeviceAddress));
    HeaderTo->appendChild(toText);

    // Create Body
    // Create a child element
    xercesc::DOMElement* Body = xmlDoc->createElementNS(xercesc::XMLString::transcode(SoapNameSpaceUri),
                                                        xercesc::XMLString::transcode(SoapBodyName));
    Envelope->appendChild(Body);

    xercesc::DOMElement* Probe = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                        xercesc::XMLString::transcode("mb:Probe"));
    Body->appendChild(Probe);

    xercesc::DOMElement* ProbeType = xmlDoc->createElement(xercesc::XMLString::transcode("mb:Type"));
    Probe->appendChild(ProbeType);

    xercesc::DOMText* TypeName = xmlDoc->createTextNode(xercesc::XMLString::transcode(ThisDeviceName));
    ProbeType->appendChild(TypeName);


    // Serialize the XML document to standard output
    xercesc::DOMImplementationLS* domImplementationLS = dynamic_cast<xercesc::DOMImplementationLS*>(domImplementation);
    if (domImplementationLS != nullptr) {
        xercesc::DOMLSSerializer* serializer = domImplementationLS->createLSSerializer();
        XMLCh* xmlString = serializer->writeToString(xmlDoc);

        //std::cout << xercesc::XMLString::transcode(xmlString) << std::endl;

        std::string xmlMessage{xercesc::XMLString::transcode(xmlString)};

        // Don't forget to release the memory
        xercesc::XMLString::release(&xmlString);
        serializer->release();
        return xmlMessage;
    }
    return std::string{""};
}

std::string PrepareGetDataBaseMessage(){
    // Get the implementation of the DOM
    xercesc::DOMImplementation* domImplementation = xercesc::DOMImplementationRegistry::getDOMImplementation(xercesc::XMLString::transcode("Core"));

    // Create a DOM document
    xercesc::DOMDocument* xmlDoc = domImplementation->createDocument(xercesc::XMLString::transcode(SoapNameSpaceUri),
                                                                     xercesc::XMLString::transcode(SoapEnvelopeName),
                                                                     0);
    // Get the root element
    xercesc::DOMElement* Envelope = xmlDoc->getDocumentElement();

    // Crate Header
    xercesc::DOMElement* Header = xmlDoc->createElementNS(xercesc::XMLString::transcode(SoapNameSpaceUri),
                                                          xercesc::XMLString::transcode(SoapHeaderName));
    Envelope->appendChild(Header);
    xercesc::DOMElement* HeaderAddress = xmlDoc->createElementNS(xercesc::XMLString::transcode(WsAddressingUri),
                                                                 xercesc::XMLString::transcode(AddressName));
    Header->appendChild(HeaderAddress);
    xercesc::DOMText* addressText = xmlDoc->createTextNode(xercesc::XMLString::transcode(ThisDeviceAddress));
    HeaderAddress->appendChild(addressText);
    xercesc::DOMElement* HeaderTo = xmlDoc->createElementNS(xercesc::XMLString::transcode(WsAddressingUri),
                                                            xercesc::XMLString::transcode(ToName));
    Header->appendChild(HeaderTo);
    xercesc::DOMText* toText = xmlDoc->createTextNode(xercesc::XMLString::transcode(ThisDeviceAddress));
    HeaderTo->appendChild(toText);

    // Create Body
    xercesc::DOMElement* Body = xmlDoc->createElementNS(xercesc::XMLString::transcode(SoapNameSpaceUri),
                                                        xercesc::XMLString::transcode(SoapBodyName));
    Envelope->appendChild(Body);
    xercesc::DOMElement* Database = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                              xercesc::XMLString::transcode("mb:DataBase"));
    Body->appendChild(Database);
    xercesc::DOMText* databaseText = xmlDoc->createTextNode(xercesc::XMLString::transcode("GetData"));
    Database->appendChild(databaseText);

    // Serialize the XML document to standard output
    xercesc::DOMImplementationLS* domImplementationLS = dynamic_cast<xercesc::DOMImplementationLS*>(domImplementation);
    if (domImplementationLS != nullptr) {
        xercesc::DOMLSSerializer* serializer = domImplementationLS->createLSSerializer();
        XMLCh* xmlString = serializer->writeToString(xmlDoc);
        std::string xmlMessage{xercesc::XMLString::transcode(xmlString)};
        // Don't forget to release the memory
        xercesc::XMLString::release(&xmlString);
        serializer->release();
        return xmlMessage;
    }
    return std::string{""};
}

std::string PrepareSubscribeMessage(){
    // Get the implementation of the DOM
    xercesc::DOMImplementation* domImplementation = xercesc::DOMImplementationRegistry::getDOMImplementation(xercesc::XMLString::transcode("Core"));

    // Create a DOM document
    xercesc::DOMDocument* xmlDoc = domImplementation->createDocument(xercesc::XMLString::transcode(SoapNameSpaceUri),
                                                                     xercesc::XMLString::transcode(SoapEnvelopeName),
                                                                     0);
    // Get the root element
    xercesc::DOMElement* Envelope = xmlDoc->getDocumentElement();

    // Crate Header
    xercesc::DOMElement* Header = xmlDoc->createElementNS(xercesc::XMLString::transcode(SoapNameSpaceUri),
                                                          xercesc::XMLString::transcode(SoapHeaderName));
    Envelope->appendChild(Header);
    xercesc::DOMElement* HeaderAddress = xmlDoc->createElementNS(xercesc::XMLString::transcode(WsAddressingUri),
                                                                 xercesc::XMLString::transcode(AddressName));
    Header->appendChild(HeaderAddress);
    xercesc::DOMText* addressText = xmlDoc->createTextNode(xercesc::XMLString::transcode(ThisDeviceAddress));
    HeaderAddress->appendChild(addressText);
    xercesc::DOMElement* HeaderTo = xmlDoc->createElementNS(xercesc::XMLString::transcode(WsAddressingUri),
                                                            xercesc::XMLString::transcode(ToName));
    Header->appendChild(HeaderTo);
    xercesc::DOMText* toText = xmlDoc->createTextNode(xercesc::XMLString::transcode(ThisDeviceAddress));
    HeaderTo->appendChild(toText);

    // Create Body
    xercesc::DOMElement* Body = xmlDoc->createElementNS(xercesc::XMLString::transcode(SoapNameSpaceUri),
                                                        xercesc::XMLString::transcode(SoapBodyName));
    Envelope->appendChild(Body);
    xercesc::DOMElement* Subsscribe = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                            xercesc::XMLString::transcode("mb:Subscribe"));
    Body->appendChild(Subsscribe);

    xercesc::DOMElement* SubsscribeElements = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                              xercesc::XMLString::transcode("mb:SubscribeElements"));
    Subsscribe->appendChild(SubsscribeElements);
    xercesc::DOMText* elementsText = xmlDoc->createTextNode(xercesc::XMLString::transcode("ReportTypeA, ReportTypeB"));
    SubsscribeElements->appendChild(elementsText);

    // Serialize the XML document to standard output
    xercesc::DOMImplementationLS* domImplementationLS = dynamic_cast<xercesc::DOMImplementationLS*>(domImplementation);
    if (domImplementationLS != nullptr) {
        xercesc::DOMLSSerializer* serializer = domImplementationLS->createLSSerializer();
        XMLCh* xmlString = serializer->writeToString(xmlDoc);
        std::string xmlMessage{xercesc::XMLString::transcode(xmlString)};
        // Don't forget to release the memory
        xercesc::XMLString::release(&xmlString);
        serializer->release();
        return xmlMessage;
    }
    return std::string{""};
}
std::string PrepareUnsubscribeMessage()
{
    // Get the implementation of the DOM
    xercesc::DOMImplementation* domImplementation = xercesc::DOMImplementationRegistry::getDOMImplementation(xercesc::XMLString::transcode("Core"));

    // Create a DOM document
    xercesc::DOMDocument* xmlDoc = domImplementation->createDocument(xercesc::XMLString::transcode(SoapNameSpaceUri),
                                                                     xercesc::XMLString::transcode(SoapEnvelopeName),
                                                                     0);
    // Get the root element
    xercesc::DOMElement* Envelope = xmlDoc->getDocumentElement();

    // Crate Header
    xercesc::DOMElement* Header = xmlDoc->createElementNS(xercesc::XMLString::transcode(SoapNameSpaceUri),
                                                          xercesc::XMLString::transcode(SoapHeaderName));
    Envelope->appendChild(Header);
    xercesc::DOMElement* HeaderAddress = xmlDoc->createElementNS(xercesc::XMLString::transcode(WsAddressingUri),
                                                                 xercesc::XMLString::transcode(AddressName));
    Header->appendChild(HeaderAddress);
    xercesc::DOMText* addressText = xmlDoc->createTextNode(xercesc::XMLString::transcode(ThisDeviceAddress));
    HeaderAddress->appendChild(addressText);
    xercesc::DOMElement* HeaderTo = xmlDoc->createElementNS(xercesc::XMLString::transcode(WsAddressingUri),
                                                            xercesc::XMLString::transcode(ToName));
    Header->appendChild(HeaderTo);
    xercesc::DOMText* toText = xmlDoc->createTextNode(xercesc::XMLString::transcode(ThisDeviceAddress));
    HeaderTo->appendChild(toText);

    // Create Body
    xercesc::DOMElement* Body = xmlDoc->createElementNS(xercesc::XMLString::transcode(SoapNameSpaceUri),
                                                        xercesc::XMLString::transcode(SoapBodyName));
    Envelope->appendChild(Body);
    xercesc::DOMElement* Unsubscribe = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                              xercesc::XMLString::transcode("mb:Unsubscribe"));
    Body->appendChild(Unsubscribe);
    xercesc::DOMText* unsubText = xmlDoc->createTextNode(xercesc::XMLString::transcode("unsubscribe"));
    Unsubscribe->appendChild(unsubText);


    // Serialize the XML document to standard output
    xercesc::DOMImplementationLS* domImplementationLS = dynamic_cast<xercesc::DOMImplementationLS*>(domImplementation);
    if (domImplementationLS != nullptr) {
        xercesc::DOMLSSerializer* serializer = domImplementationLS->createLSSerializer();
        XMLCh* xmlString = serializer->writeToString(xmlDoc);
        std::string xmlMessage{xercesc::XMLString::transcode(xmlString)};
        // Don't forget to release the memory
        xercesc::XMLString::release(&xmlString);
        serializer->release();
        return xmlMessage;
    }
    return std::string{""};
}

std::string PrepareReportTypeAresponseMessage();    // TODO
std::string PrepareReportTypeBresponseMessage();    // TODO
std::string PrepareSetCommandOneMessage();          // TODO
std::string PrepareSetCommandTwoMessage();          // TODO

std::string PrepareGracefullyDisconnectMessage(){
    return "Bye from Medical-Device";
}

std::string PrepareStartReports(){
    // Get the implementation of the DOM
    xercesc::DOMImplementation* domImplementation = xercesc::DOMImplementationRegistry::getDOMImplementation(xercesc::XMLString::transcode("Core"));

    // Create a DOM document
    xercesc::DOMDocument* xmlDoc = domImplementation->createDocument(xercesc::XMLString::transcode(SoapNameSpaceUri),
                                                                     xercesc::XMLString::transcode(SoapEnvelopeName),
                                                                     0);
    // Get the root element
    xercesc::DOMElement* Envelope = xmlDoc->getDocumentElement();

    // Crate Header
    xercesc::DOMElement* Header = xmlDoc->createElementNS(xercesc::XMLString::transcode(SoapNameSpaceUri),
                                                          xercesc::XMLString::transcode(SoapHeaderName));
    Envelope->appendChild(Header);
    xercesc::DOMElement* HeaderAddress = xmlDoc->createElementNS(xercesc::XMLString::transcode(WsAddressingUri),
                                                                 xercesc::XMLString::transcode(AddressName));
    Header->appendChild(HeaderAddress);
    xercesc::DOMText* addressText = xmlDoc->createTextNode(xercesc::XMLString::transcode(ThisDeviceAddress));
    HeaderAddress->appendChild(addressText);
    xercesc::DOMElement* HeaderTo = xmlDoc->createElementNS(xercesc::XMLString::transcode(WsAddressingUri),
                                                            xercesc::XMLString::transcode(ToName));
    Header->appendChild(HeaderTo);
    xercesc::DOMText* toText = xmlDoc->createTextNode(xercesc::XMLString::transcode(ThisDeviceAddress));
    HeaderTo->appendChild(toText);

    // Create Body
    xercesc::DOMElement* Body = xmlDoc->createElementNS(xercesc::XMLString::transcode(SoapNameSpaceUri),
                                                        xercesc::XMLString::transcode(SoapBodyName));
    Envelope->appendChild(Body);
    xercesc::DOMElement* StartReports = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                               xercesc::XMLString::transcode("mb:StartReports"));
    Body->appendChild(StartReports);
    xercesc::DOMText* startText = xmlDoc->createTextNode(xercesc::XMLString::transcode("START."));
    StartReports->appendChild(startText);


    // Serialize the XML document to standard output
    xercesc::DOMImplementationLS* domImplementationLS = dynamic_cast<xercesc::DOMImplementationLS*>(domImplementation);
    if (domImplementationLS != nullptr) {
        xercesc::DOMLSSerializer* serializer = domImplementationLS->createLSSerializer();
        XMLCh* xmlString = serializer->writeToString(xmlDoc);
        std::string xmlMessage{xercesc::XMLString::transcode(xmlString)};
        // Don't forget to release the memory
        xercesc::XMLString::release(&xmlString);
        serializer->release();
        return xmlMessage;
    }
    return std::string{""};
}

std::string PrepareReportTypeAresponseMessage() {
    // Get the implementation of the DOM
    xercesc::DOMImplementation* domImplementation = xercesc::DOMImplementationRegistry::getDOMImplementation(xercesc::XMLString::transcode("Core"));

    // Create a DOM document
    xercesc::DOMDocument* xmlDoc = domImplementation->createDocument(xercesc::XMLString::transcode(SoapNameSpaceUri),
                                                                     xercesc::XMLString::transcode(SoapEnvelopeName),
                                                                     0);
    // Get the root element
    xercesc::DOMElement* Envelope = xmlDoc->getDocumentElement();

    // Crate Header
    xercesc::DOMElement* Header = xmlDoc->createElementNS(xercesc::XMLString::transcode(SoapNameSpaceUri),
                                                          xercesc::XMLString::transcode(SoapHeaderName));
    Envelope->appendChild(Header);
    xercesc::DOMElement* HeaderAddress = xmlDoc->createElementNS(xercesc::XMLString::transcode(WsAddressingUri),
                                                                 xercesc::XMLString::transcode(AddressName));
    Header->appendChild(HeaderAddress);
    xercesc::DOMText* addressText = xmlDoc->createTextNode(xercesc::XMLString::transcode(ThisDeviceAddress));
    HeaderAddress->appendChild(addressText);
    xercesc::DOMElement* HeaderTo = xmlDoc->createElementNS(xercesc::XMLString::transcode(WsAddressingUri),
                                                            xercesc::XMLString::transcode(ToName));
    Header->appendChild(HeaderTo);
    xercesc::DOMText* toText = xmlDoc->createTextNode(xercesc::XMLString::transcode(ThisDeviceAddress));
    HeaderTo->appendChild(toText);

    // Create Body
    xercesc::DOMElement* Body = xmlDoc->createElementNS(xercesc::XMLString::transcode(SoapNameSpaceUri),
                                                        xercesc::XMLString::transcode(SoapBodyName));
    Envelope->appendChild(Body);
    xercesc::DOMElement* StartReports = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                                xercesc::XMLString::transcode("mb:ReportTypeAResponse"));
    Body->appendChild(StartReports);
    xercesc::DOMText* startText = xmlDoc->createTextNode(xercesc::XMLString::transcode(reportAresponse));
    StartReports->appendChild(startText);


    // Serialize the XML document to standard output
    xercesc::DOMImplementationLS* domImplementationLS = dynamic_cast<xercesc::DOMImplementationLS*>(domImplementation);
    if (domImplementationLS != nullptr) {
        xercesc::DOMLSSerializer* serializer = domImplementationLS->createLSSerializer();
        XMLCh* xmlString = serializer->writeToString(xmlDoc);
        std::string xmlMessage{xercesc::XMLString::transcode(xmlString)};
        // Don't forget to release the memory
        xercesc::XMLString::release(&xmlString);
        serializer->release();
        return xmlMessage;
    }
    return std::string{""};
}
std::string PrepareReportTypeBresponseMessage() {
    // Get the implementation of the DOM
    xercesc::DOMImplementation* domImplementation = xercesc::DOMImplementationRegistry::getDOMImplementation(xercesc::XMLString::transcode("Core"));

    // Create a DOM document
    xercesc::DOMDocument* xmlDoc = domImplementation->createDocument(xercesc::XMLString::transcode(SoapNameSpaceUri),
                                                                     xercesc::XMLString::transcode(SoapEnvelopeName),
                                                                     0);
    // Get the root element
    xercesc::DOMElement* Envelope = xmlDoc->getDocumentElement();

    // Crate Header
    xercesc::DOMElement* Header = xmlDoc->createElementNS(xercesc::XMLString::transcode(SoapNameSpaceUri),
                                                          xercesc::XMLString::transcode(SoapHeaderName));
    Envelope->appendChild(Header);
    xercesc::DOMElement* HeaderAddress = xmlDoc->createElementNS(xercesc::XMLString::transcode(WsAddressingUri),
                                                                 xercesc::XMLString::transcode(AddressName));
    Header->appendChild(HeaderAddress);
    xercesc::DOMText* addressText = xmlDoc->createTextNode(xercesc::XMLString::transcode(ThisDeviceAddress));
    HeaderAddress->appendChild(addressText);
    xercesc::DOMElement* HeaderTo = xmlDoc->createElementNS(xercesc::XMLString::transcode(WsAddressingUri),
                                                            xercesc::XMLString::transcode(ToName));
    Header->appendChild(HeaderTo);
    xercesc::DOMText* toText = xmlDoc->createTextNode(xercesc::XMLString::transcode(ThisDeviceAddress));
    HeaderTo->appendChild(toText);

    // Create Body
    xercesc::DOMElement* Body = xmlDoc->createElementNS(xercesc::XMLString::transcode(SoapNameSpaceUri),
                                                        xercesc::XMLString::transcode(SoapBodyName));
    Envelope->appendChild(Body);
    xercesc::DOMElement* StartReports = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                                xercesc::XMLString::transcode("mb:ReportTypeBResponse"));
    Body->appendChild(StartReports);
    xercesc::DOMText* startText = xmlDoc->createTextNode(xercesc::XMLString::transcode(reportBresponse));
    StartReports->appendChild(startText);


    // Serialize the XML document to standard output
    xercesc::DOMImplementationLS* domImplementationLS = dynamic_cast<xercesc::DOMImplementationLS*>(domImplementation);
    if (domImplementationLS != nullptr) {
        xercesc::DOMLSSerializer* serializer = domImplementationLS->createLSSerializer();
        XMLCh* xmlString = serializer->writeToString(xmlDoc);
        std::string xmlMessage{xercesc::XMLString::transcode(xmlString)};
        // Don't forget to release the memory
        xercesc::XMLString::release(&xmlString);
        serializer->release();
        return xmlMessage;
    }
    return std::string{""};
}

std::string PrepareSetCommandOneMessage(std::string patientID,
                                        std::string operation){
    // Get the implementation of the DOM
    xercesc::DOMImplementation* domImplementation = xercesc::DOMImplementationRegistry::getDOMImplementation(xercesc::XMLString::transcode("Core"));

    // Create a DOM document
    xercesc::DOMDocument* xmlDoc = domImplementation->createDocument(xercesc::XMLString::transcode(SoapNameSpaceUri),
                                                                     xercesc::XMLString::transcode(SoapEnvelopeName),
                                                                     0);
    // Get the root element
    xercesc::DOMElement* Envelope = xmlDoc->getDocumentElement();

    // Crate Header
    xercesc::DOMElement* Header = xmlDoc->createElementNS(xercesc::XMLString::transcode(SoapNameSpaceUri),
                                                          xercesc::XMLString::transcode(SoapHeaderName));
    Envelope->appendChild(Header);
    xercesc::DOMElement* HeaderAddress = xmlDoc->createElementNS(xercesc::XMLString::transcode(WsAddressingUri),
                                                                 xercesc::XMLString::transcode(AddressName));
    Header->appendChild(HeaderAddress);
    xercesc::DOMText* addressText = xmlDoc->createTextNode(xercesc::XMLString::transcode(ThisDeviceAddress));
    HeaderAddress->appendChild(addressText);
    xercesc::DOMElement* HeaderTo = xmlDoc->createElementNS(xercesc::XMLString::transcode(WsAddressingUri),
                                                            xercesc::XMLString::transcode(ToName));
    Header->appendChild(HeaderTo);
    xercesc::DOMText* toText = xmlDoc->createTextNode(xercesc::XMLString::transcode(ThisDeviceAddress));
    HeaderTo->appendChild(toText);

    // Create Body
    xercesc::DOMElement* Body = xmlDoc->createElementNS(xercesc::XMLString::transcode(SoapNameSpaceUri),
                                                        xercesc::XMLString::transcode(SoapBodyName));
    Envelope->appendChild(Body);
    xercesc::DOMElement* SetCommandOne = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                               xercesc::XMLString::transcode("mb:SetCommandOne"));
    Body->appendChild(SetCommandOne);
    xercesc::DOMElement* patID = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                         xercesc::XMLString::transcode("mb:PatientID"));
    SetCommandOne->appendChild(patID);
    xercesc::DOMText* idValue = xmlDoc->createTextNode(xercesc::XMLString::transcode(patientID.data()));
    patID->appendChild(idValue);

    xercesc::DOMElement* patOperation = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                         xercesc::XMLString::transcode("mb:Operation"));
    SetCommandOne->appendChild(patOperation);
    xercesc::DOMText* operationValue = xmlDoc->createTextNode(xercesc::XMLString::transcode(operation.data()));
    patOperation->appendChild(operationValue);

    // Get current time
    auto currentTime = std::chrono::system_clock::now();
    // Convert the time point to a time_t (seconds since epoch)
    std::time_t currentTimeT = std::chrono::system_clock::to_time_t(currentTime);
    // Format the time as a string
    char timeBuffer[80];
    std::strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", std::localtime(&currentTimeT));
    // Store the formatted time in a std::string
    std::string formattedTime(timeBuffer);

    xercesc::DOMElement* currTime = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                            xercesc::XMLString::transcode("mb:CurrentTime"));
    SetCommandOne->appendChild(currTime);
    xercesc::DOMText* currTimeValue = xmlDoc->createTextNode(xercesc::XMLString::transcode(formattedTime.data()));
    currTime->appendChild(currTimeValue);


    // Serialize the XML document to standard output
    xercesc::DOMImplementationLS* domImplementationLS = dynamic_cast<xercesc::DOMImplementationLS*>(domImplementation);
    if (domImplementationLS != nullptr) {
        xercesc::DOMLSSerializer* serializer = domImplementationLS->createLSSerializer();
        XMLCh* xmlString = serializer->writeToString(xmlDoc);
        std::string xmlMessage{xercesc::XMLString::transcode(xmlString)};
        // Don't forget to release the memory
        xercesc::XMLString::release(&xmlString);
        serializer->release();
        return xmlMessage;
    }
    return std::string{""};
}

std::string PrepareSetCommandTwoMessage(std::string patientID,
                                        std::string operation,
                                        std::string value) {
    // Get the implementation of the DOM
    xercesc::DOMImplementation* domImplementation = xercesc::DOMImplementationRegistry::getDOMImplementation(xercesc::XMLString::transcode("Core"));

    // Create a DOM document
    xercesc::DOMDocument* xmlDoc = domImplementation->createDocument(xercesc::XMLString::transcode(SoapNameSpaceUri),
                                                                     xercesc::XMLString::transcode(SoapEnvelopeName),
                                                                     0);
    // Get the root element
    xercesc::DOMElement* Envelope = xmlDoc->getDocumentElement();

    // Crate Header
    xercesc::DOMElement* Header = xmlDoc->createElementNS(xercesc::XMLString::transcode(SoapNameSpaceUri),
                                                          xercesc::XMLString::transcode(SoapHeaderName));
    Envelope->appendChild(Header);
    xercesc::DOMElement* HeaderAddress = xmlDoc->createElementNS(xercesc::XMLString::transcode(WsAddressingUri),
                                                                 xercesc::XMLString::transcode(AddressName));
    Header->appendChild(HeaderAddress);
    xercesc::DOMText* addressText = xmlDoc->createTextNode(xercesc::XMLString::transcode(ThisDeviceAddress));
    HeaderAddress->appendChild(addressText);
    xercesc::DOMElement* HeaderTo = xmlDoc->createElementNS(xercesc::XMLString::transcode(WsAddressingUri),
                                                            xercesc::XMLString::transcode(ToName));
    Header->appendChild(HeaderTo);
    xercesc::DOMText* toText = xmlDoc->createTextNode(xercesc::XMLString::transcode(ThisDeviceAddress));
    HeaderTo->appendChild(toText);

    // Create Body
    xercesc::DOMElement* Body = xmlDoc->createElementNS(xercesc::XMLString::transcode(SoapNameSpaceUri),
                                                        xercesc::XMLString::transcode(SoapBodyName));
    Envelope->appendChild(Body);
    xercesc::DOMElement* SetCommandTwo = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                                 xercesc::XMLString::transcode("mb:SetCommandTwo"));
    Body->appendChild(SetCommandTwo);
    xercesc::DOMElement* patID = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                         xercesc::XMLString::transcode("mb:PatientID"));
    SetCommandTwo->appendChild(patID);
    xercesc::DOMText* idValue = xmlDoc->createTextNode(xercesc::XMLString::transcode(patientID.data()));
    patID->appendChild(idValue);

    xercesc::DOMElement* patOperation = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                                xercesc::XMLString::transcode("mb:Operation"));
    SetCommandTwo->appendChild(patOperation);
    xercesc::DOMText* operationValue = xmlDoc->createTextNode(xercesc::XMLString::transcode(operation.data()));
    patOperation->appendChild(operationValue);

    xercesc::DOMElement* patOpValue = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                                xercesc::XMLString::transcode("mb:OperationValue"));
    SetCommandTwo->appendChild(patOpValue);
    xercesc::DOMText* patOpValueVal = xmlDoc->createTextNode(xercesc::XMLString::transcode(value.data()));
    patOpValue->appendChild(patOpValueVal);

    // Get current time
    auto currentTime = std::chrono::system_clock::now();
    // Convert the time point to a time_t (seconds since epoch)
    std::time_t currentTimeT = std::chrono::system_clock::to_time_t(currentTime);
    // Format the time as a string
    char timeBuffer[80];
    std::strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", std::localtime(&currentTimeT));
    // Store the formatted time in a std::string
    std::string formattedTime(timeBuffer);

    xercesc::DOMElement* currTime = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                            xercesc::XMLString::transcode("mb:CurrentTime"));
    SetCommandTwo->appendChild(currTime);
    xercesc::DOMText* currTimeValue = xmlDoc->createTextNode(xercesc::XMLString::transcode(formattedTime.data()));
    currTime->appendChild(currTimeValue);


    // Serialize the XML document to standard output
    xercesc::DOMImplementationLS* domImplementationLS = dynamic_cast<xercesc::DOMImplementationLS*>(domImplementation);
    if (domImplementationLS != nullptr) {
        xercesc::DOMLSSerializer* serializer = domImplementationLS->createLSSerializer();
        XMLCh* xmlString = serializer->writeToString(xmlDoc);
        std::string xmlMessage{xercesc::XMLString::transcode(xmlString)};
        // Don't forget to release the memory
        xercesc::XMLString::release(&xmlString);
        serializer->release();
        return xmlMessage;
    }
    return std::string{""};
}


} // ApplicationLogic
