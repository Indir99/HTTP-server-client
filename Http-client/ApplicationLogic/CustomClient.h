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
    UnsubscribeResponse,
    ReportTypeA,
    ReportTypeAresponse,
    ReportTypeB,
    ReportTypeBresponse
};

const std::string hello{"Hello from Client"};
const std::string probe{"Client send Probe"};
const std::string getDataBase{"Client want dataBase"};
const std::string subscribe{"Client want to subscribe to some reports"};
const std::string unsubscribe{"Client want to unsubscribe"};
const std::string reportAresponse{"ReportA received successfully"};
const std::string reportBresponse{"ReportB received successfully"};

class CustomClient : public Networking::ClientInterface<CustomMsgTypes>
{
public:
    void Hello()
    {
        Networking::Message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::Hello;
        msg << hello.data();
        Send(msg);
    }

    void Probe()
    {
        Networking::Message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::Probe;
        msg << probe.data();
        Send(msg);
    }

    void GetDataBase()
    {
        Networking::Message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::GetDataBase;
        msg << getDataBase.data();
        Send(msg);
    }

    void Subscribe()
    {
        Networking::Message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::Subscribe;
        msg << subscribe.data();
        Send(msg);
    }

    void Unsubscribe()
    {
        Networking::Message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::Unsubscribe;
        msg << unsubscribe.data();
        Send(msg);
    }

    void ReportTypeAresponse()
    {
        Networking::Message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::ReportTypeAresponse;
        msg << reportAresponse.data();
        Send(msg);
    }

    void ReportTypeBresponse()
    {
        Networking::Message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::ReportTypeBresponse;
        msg << reportBresponse.data();
        Send(msg);
    }
};
} // ApplicationLogic
