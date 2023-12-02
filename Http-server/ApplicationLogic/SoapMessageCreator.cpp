#include "SoapMessageCreator.h"
#include <chrono>
#include <iostream>

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
    return "Hello from Medical-Server";
}

std::string PrepareServerAcceptMessage(){
    return "Server accepted connection";
}

std::string PrepareServerDenyMessage(){
    return "Server denied connection";
}

std::string PrepareProbeMatchMessage(){
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

    xercesc::DOMElement* ProbeMatch = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                        xercesc::XMLString::transcode("mb:ProbeMatch"));
    Body->appendChild(ProbeMatch);

    xercesc::DOMElement* ProbeMatchType = xmlDoc->createElement(xercesc::XMLString::transcode("mb:Type"));
    ProbeMatch->appendChild(ProbeMatchType);

    xercesc::DOMText* TypeName = xmlDoc->createTextNode(xercesc::XMLString::transcode(ThisDeviceName));
    ProbeMatchType->appendChild(TypeName);


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

std::string PrepareGetDataBaseResponseMessage(){
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
    xercesc::DOMElement* DatabaseElement = xmlDoc->createElement(xercesc::XMLString::transcode("mb:Patient"));
    Database->appendChild(DatabaseElement);
    xercesc::DOMText* patientText = xmlDoc->createTextNode(xercesc::XMLString::transcode("Patient data"));
    DatabaseElement->appendChild(patientText);
    xercesc::DOMElement* DatabaseElement2 = xmlDoc->createElement(xercesc::XMLString::transcode("mb:Doctor"));
    Database->appendChild(DatabaseElement2);
    xercesc::DOMText* doctorText = xmlDoc->createTextNode(xercesc::XMLString::transcode("Doctor data"));
    DatabaseElement2->appendChild(doctorText);
    xercesc::DOMElement* DatabaseElement3 = xmlDoc->createElement(xercesc::XMLString::transcode("mb:Therapy"));
    Database->appendChild(DatabaseElement3);
    xercesc::DOMText* therapyText = xmlDoc->createTextNode(xercesc::XMLString::transcode("Therapy data"));
    DatabaseElement3->appendChild(therapyText);
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

std::string PrepareSubscribeResponseMessage(){
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
                                                            xercesc::XMLString::transcode("mb:SubscribeResponse"));
    Body->appendChild(Subsscribe);

    xercesc::DOMElement* SubsscribeElements = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                              xercesc::XMLString::transcode("mb:SubscribedElements"));
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
std::string PrepareUnsubscribeResponseMessage()
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
                                                              xercesc::XMLString::transcode("mb:UnsubscribeResponse"));
    Body->appendChild(Unsubscribe);
    xercesc::DOMText* unsubText = xmlDoc->createTextNode(xercesc::XMLString::transcode("Successfully"));
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

std::string PrepareStoppingReportsMessage(){
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
    xercesc::DOMElement* StopReports = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                               xercesc::XMLString::transcode("mb:StopReports"));
    Body->appendChild(StopReports);
    xercesc::DOMText* stopText = xmlDoc->createTextNode(xercesc::XMLString::transcode("DONE."));
    StopReports->appendChild(stopText);


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


std::string PrepareReportTypeAmessage(std::string patientID,
                                      std::string patientFirstName,
                                      std::string patientLastName,
                                      std::string bloodPressure,
                                      std::string temperature,
                                      std::string heartRate){

    xercesc::DOMImplementation* domImplementation = xercesc::DOMImplementationRegistry::getDOMImplementation(xercesc::XMLString::transcode("Core"));
    xercesc::DOMDocument* xmlDoc = domImplementation->createDocument(xercesc::XMLString::transcode(SoapNameSpaceUri),
                                                                     xercesc::XMLString::transcode(SoapEnvelopeName),
                                                                     0);
    xercesc::DOMElement* Envelope = xmlDoc->getDocumentElement();
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
    xercesc::DOMElement* ReportTypeA = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                               xercesc::XMLString::transcode("mb:ReportTypeA"));
    Body->appendChild(ReportTypeA);
    xercesc::DOMElement* patID = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                               xercesc::XMLString::transcode("mb:PatientID"));
    ReportTypeA->appendChild(patID);
    xercesc::DOMText* idValue = xmlDoc->createTextNode(xercesc::XMLString::transcode(patientID.data()));
    patID->appendChild(idValue);

    xercesc::DOMElement* patFirstName = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                         xercesc::XMLString::transcode("mb:PatientFirstName"));
    ReportTypeA->appendChild(patFirstName);
    xercesc::DOMText* firstNameValue = xmlDoc->createTextNode(xercesc::XMLString::transcode(patientFirstName.data()));
    patFirstName->appendChild(firstNameValue);

    xercesc::DOMElement* patLasttName = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                                xercesc::XMLString::transcode("mb:PatientLastName"));
    ReportTypeA->appendChild(patLasttName);
    xercesc::DOMText* lastNameValue = xmlDoc->createTextNode(xercesc::XMLString::transcode(patientLastName.data()));
    patLasttName->appendChild(lastNameValue);

    xercesc::DOMElement* patbloodPressure = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                         xercesc::XMLString::transcode("mb:PatientBloodPressure"));
    ReportTypeA->appendChild(patbloodPressure);
    xercesc::DOMText* bloodPressureValue = xmlDoc->createTextNode(xercesc::XMLString::transcode(bloodPressure.data()));
    patbloodPressure->appendChild(bloodPressureValue);

    xercesc::DOMElement* patTemperature = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                         xercesc::XMLString::transcode("mb:PatientTemperature"));
    ReportTypeA->appendChild(patTemperature);
    xercesc::DOMText* temperatureValue = xmlDoc->createTextNode(xercesc::XMLString::transcode(temperature.data()));
    patTemperature->appendChild(temperatureValue);

    xercesc::DOMElement* patHeartRate = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                                  xercesc::XMLString::transcode("mb:PatientHeartRate"));
    ReportTypeA->appendChild(patHeartRate);
    xercesc::DOMText* heartRateValue = xmlDoc->createTextNode(xercesc::XMLString::transcode(heartRate.data()));
    patHeartRate->appendChild(heartRateValue);

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
    ReportTypeA->appendChild(currTime);
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
std::string PrepareReportTypeBmessage(std::string patientID,
                                      std::string patientFirstName,
                                      std::string patientLastName,
                                      std::string doctorID,
                                      std::string doctorFirstName,
                                      std::string doctorLastName,
                                      std::string therapyName,
                                      std::string therapyStatus){
    xercesc::DOMImplementation* domImplementation = xercesc::DOMImplementationRegistry::getDOMImplementation(xercesc::XMLString::transcode("Core"));
    xercesc::DOMDocument* xmlDoc = domImplementation->createDocument(xercesc::XMLString::transcode(SoapNameSpaceUri),
                                                                     xercesc::XMLString::transcode(SoapEnvelopeName),
                                                                     0);
    xercesc::DOMElement* Envelope = xmlDoc->getDocumentElement();
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
    xercesc::DOMElement* ReportTypeB = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                               xercesc::XMLString::transcode("mb:ReportTypeB"));
    Body->appendChild(ReportTypeB);
    xercesc::DOMElement* patID = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                         xercesc::XMLString::transcode("mb:PatientID"));
    ReportTypeB->appendChild(patID);
    xercesc::DOMText* idValue = xmlDoc->createTextNode(xercesc::XMLString::transcode(patientID.data()));
    patID->appendChild(idValue);

    xercesc::DOMElement* patFirstName = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                                xercesc::XMLString::transcode("mb:PatientFirstName"));
    ReportTypeB->appendChild(patFirstName);
    xercesc::DOMText* firstNameValue = xmlDoc->createTextNode(xercesc::XMLString::transcode(patientFirstName.data()));
    patFirstName->appendChild(firstNameValue);

    xercesc::DOMElement* patLasttName = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                                xercesc::XMLString::transcode("mb:PatientLastName"));
    ReportTypeB->appendChild(patLasttName);
    xercesc::DOMText* lastNameValue = xmlDoc->createTextNode(xercesc::XMLString::transcode(patientLastName.data()));
    patLasttName->appendChild(lastNameValue);

    xercesc::DOMElement* docID = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                         xercesc::XMLString::transcode("mb:DoctorID"));
    ReportTypeB->appendChild(docID);
    xercesc::DOMText* docidValue = xmlDoc->createTextNode(xercesc::XMLString::transcode(doctorID.data()));
    docID->appendChild(docidValue);

    xercesc::DOMElement* docFirstName = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                                xercesc::XMLString::transcode("mb:DoctorFirstName"));
    ReportTypeB->appendChild(docFirstName);
    xercesc::DOMText* docFirstNameValue = xmlDoc->createTextNode(xercesc::XMLString::transcode(doctorFirstName.data()));
    docFirstName->appendChild(docFirstNameValue);

    xercesc::DOMElement* docLasttName = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                                xercesc::XMLString::transcode("mb:DoctorLastName"));
    ReportTypeB->appendChild(docLasttName);
    xercesc::DOMText* docLastNameValue = xmlDoc->createTextNode(xercesc::XMLString::transcode(doctorLastName.data()));
    docLasttName->appendChild(docLastNameValue);

    xercesc::DOMElement* patTherapyName = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                                xercesc::XMLString::transcode("mb:TherapyName"));
    ReportTypeB->appendChild(patTherapyName);
    xercesc::DOMText* therapyNameValue = xmlDoc->createTextNode(xercesc::XMLString::transcode(therapyName.data()));
    patTherapyName->appendChild(therapyNameValue);

    xercesc::DOMElement* patTherapyStatus = xmlDoc->createElementNS(xercesc::XMLString::transcode(BodyUri),
                                                                  xercesc::XMLString::transcode("mb:TherapyStatus"));
    ReportTypeB->appendChild(patTherapyStatus);
    xercesc::DOMText* therapyStatusValue = xmlDoc->createTextNode(xercesc::XMLString::transcode(therapyStatus.data()));
    patTherapyStatus->appendChild(therapyStatusValue);

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
    ReportTypeB->appendChild(currTime);
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
std::string PrepareSetCommandOneResponseMessage(){
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
                                                                xercesc::XMLString::transcode("mb:SetCommandOneResponse"));
    Body->appendChild(StartReports);
    xercesc::DOMText* startText = xmlDoc->createTextNode(xercesc::XMLString::transcode(setOneResponse));
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
std::string PrepareSetCommandTwoResponseMessage(){
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
                                                                xercesc::XMLString::transcode("mb:SetCommandTwoResponse"));
    Body->appendChild(StartReports);
    xercesc::DOMText* startText = xmlDoc->createTextNode(xercesc::XMLString::transcode(setTwoResponse));
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

} // ApplicationLogic
