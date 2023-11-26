#pragma once

#include "../Networking/Client.h"
#include "../Networking/Message.h"

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

constexpr char hello[]{"Hello from Client"};
constexpr char probe[]{"Client send Probe"};
constexpr char getDataBase[]{"Client want dataBase"};
constexpr char subscribe[]{"Client want to subscribe to some reports"};
constexpr char unsubscribe[]{"Client want to unsubscribe"};
constexpr char reportAresponse[]{"ReportA received successfully"};
constexpr char reportBresponse[]{"ReportB received successfully"};
constexpr char startReports[]{"Client wants reports!"};
constexpr char setCommandOne[]{"Client want to set data: command one."};
constexpr char setCommandTwo[]{"Client want to set data: command two."};
constexpr char byeMessage[]{"Bye from client"};

class CustomClient : public Networking::ClientInterface<CustomMsgTypes>
{
public:
    void Hello()
    {
        Networking::Message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::Hello;
        msg << hello;
        Send(msg);
    }

    void Probe()
    {
        Networking::Message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::Probe;
        msg << probe;
        Send(msg);
    }

    void GetDataBase()
    {
        Networking::Message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::GetDataBase;
        msg << getDataBase;
        Send(msg);
    }

    void Subscribe()
    {
        Networking::Message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::Subscribe;
        msg << subscribe;
        Send(msg);
    }

    void Unsubscribe()
    {
        Networking::Message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::Unsubscribe;
        msg << unsubscribe;
        Send(msg);
    }

    void StartReports()
    {
        Networking::Message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::StartReports;
        msg << startReports;
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
        msg << byeMessage;
        Send(msg);
    }
};
} // ApplicationLogic