#pragma once

#include "../Networking/Client.h"
#include "../Networking/Message.h"
#include "SoapMessageCreator.h"

namespace ApplicationLogic{

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

constexpr char reportAresponse[]{"ReportA received successfully"};
constexpr char reportBresponse[]{"ReportB received successfully"};;
constexpr char setCommandOne[]{"Client want to set data: command one."};
constexpr char setCommandTwo[]{"Client want to set data: command two."};

class CustomClient : public Networking::ClientInterface<CustomMsgTypes>
{
public:
    void Hello()
    {
        Networking::Message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::Hello;
        msg << PrepareHelloMessage().data();
        Send(msg);
    }

    void Probe()
    {
        Networking::Message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::Probe;
        msg << PrepareProbeMessage().data();
        Send(msg);
    }

    void GetDataBase()
    {
        Networking::Message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::GetDataBase;
        msg << PrepareGetDataBaseMessage().data();
        Send(msg);
    }

    void Subscribe()
    {
        Networking::Message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::Subscribe;
        msg << PrepareSubscribeMessage().data();
        Send(msg);
    }

    void Unsubscribe()
    {
        Networking::Message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::Unsubscribe;
        msg << PrepareUnsubscribeMessage().data();
        Send(msg);
    }

    void StartReports()
    {
        Networking::Message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::StartReports;
        msg << PrepareStartReports().data();
        Send(msg);
    }

    void ReportTypeAresponse()
    {
        Networking::Message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::ReportTypeAresponse;
        msg << reportAresponse;
        Send(msg);
    }

    void ReportTypeBresponse()
    {
        Networking::Message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::ReportTypeBresponse;
        msg << reportBresponse;
        Send(msg);
    }

    void SetCommandOne()
    {
        Networking::Message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::SetCommandOne;
        msg << setCommandOne;
        Send(msg);
    }

    void SetCommandTwo()
    {
        Networking::Message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::SetCommandTwo;
        msg << setCommandTwo;
        Send(msg);
    }

    void GracefullyDisconnect()
    {
        Networking::Message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::GracefullyDisconnect;
        msg << PrepareGracefullyDisconnectMessage().data();
        Send(msg);
    }
};
} // ApplicationLogic
