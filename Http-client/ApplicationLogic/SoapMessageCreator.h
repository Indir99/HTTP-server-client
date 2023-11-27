#pragma once

#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <string>

enum class CustomMsgTypes : uint32_t
{
    ServerAccept,
    ServerDeny,
    Hello,
    Probe,
    ProbeMatch,
    GetDataBase,
    GetDataBaseResponse,
    Subscribe,
    SubscribeResponse,
    Unsubscribe,
    StartReports,
    UnsubscribeResponse,
    ReportTypeA,
    ReportTypeAresponse,
    ReportTypeB,
    ReportTypeBresponse,
    StoppingReports,
    SetCommandOne,
    SetCommandOneResponse,
    SetCommandTwo,
    SetCommandTwoResponse,
    GracefullyDisconnect
};


namespace ApplicationLogic{
void InitializeLibrary();       // Done
void DeinitializeLibrary();     // Done

std::string PrepareHelloMessage();                  // Done
std::string PrepareProbeMessage();                  // Done
std::string PrepareGetDataBaseMessage();            // Done
std::string PrepareSubscribeMessage();              // Done
std::string PrepareUnsubscribeMessage();            // Done
std::string PrepareReportTypeAresponseMessage();    // TODO
std::string PrepareReportTypeBresponseMessage();    // TODO
std::string PrepareSetCommandOneMessage();          // TODO
std::string PrepareSetCommandTwoMessage();          // TODO
std::string PrepareGracefullyDisconnectMessage();   // Done
std::string PrepareStartReports();                  // Done

} // ApplicationLogic
