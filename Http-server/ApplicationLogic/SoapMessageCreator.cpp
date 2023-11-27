#include "SoapMessageCreator.h"


namespace ApplicationLogic {


namespace {


// supported tpyes
// MedicalDeviceTypeA
// MedicalDeciveTypeB
// supported types
// MedicalServerTypeA
// MedicalServerTypeB

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


std::string PrepareReportTypeAmessage();
std::string PrepareReportTypeBmessage();
std::string PrepareSetCommandOneResponseMessage();
std::string PrepareSetCommandTwoResponseMessage();

} // ApplicationLogic
