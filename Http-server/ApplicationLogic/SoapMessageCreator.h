#pragma once

#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <string>




namespace ApplicationLogic{
void InitializeLibrary();       // Done
void DeinitializeLibrary();     // Done

std::string PrepareHelloMessage();                  // Done
std::string PrepareServerAcceptMessage();           // Done
std::string PrepareServerDenyMessage();             // Done
std::string PrepareProbeMatchMessage();             // Done
std::string PrepareGetDataBaseResponseMessage();    // Done
std::string PrepareSubscribeResponseMessage();      // Done
std::string PrepareUnsubscribeResponseMessage();    // Done
std::string PrepareReportTypeAmessage();            // TODO
std::string PrepareReportTypeBmessage();            // TODO
std::string PrepareStoppingReportsMessage();        // TODO
std::string PrepareSetCommandOneResponseMessage();  // TODO
std::string PrepareSetCommandTwoResponseMessage();  // TODO

} // ApplicationLogic
