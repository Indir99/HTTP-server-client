#include "../Networking/Message.h"
#include "../Networking/Connection.h"
#include "../Networking/Server.h"
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

constexpr char reportA[]{"Report typr A from Server"};
constexpr char reportB[]{"Report typr B from Server"};
constexpr char setOneResponse[]{"Response on set one command"};
constexpr char setTwoResponse[]{"Response on set two command"};


class CustomServer : public Networking::ServerInterface<CustomMsgTypes>
{
public:
    CustomServer(uint16_t nPort) : Networking::ServerInterface<CustomMsgTypes>(nPort)
    {

    }

protected:
    virtual bool OnClientConnect(std::shared_ptr<Networking::Connection<CustomMsgTypes>> client)
    {
        Networking::Message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::ServerAccept;
        client->Send(msg);
        return true;
    }

    // Called when a client appears to have disconnected
    virtual void OnClientDisconnect(std::shared_ptr<Networking::Connection<CustomMsgTypes>> client)
    {
        std::cout << "Removing client [" << client->GetID() << "]\n";
    }

    // Called when a message arrives
    virtual void OnMessage(std::shared_ptr<Networking::Connection<CustomMsgTypes>> client, Networking::Message<CustomMsgTypes>& msg)
    {
        switch (msg.header.id)
        {
        case CustomMsgTypes::Hello:
        {
            std::cout << "[" << client->GetID() << "]: Server recived: ";
            std::cout << msg.body <<std::endl;
            // Simply bounce message back to client
            Networking::Message<CustomMsgTypes> msgToSend;
            msgToSend.header.id = CustomMsgTypes::Hello;
            msgToSend << PrepareHelloMessage().data();
            client->Send(msgToSend);
        }
        break;

        case CustomMsgTypes::Probe:
        {
            std::cout << "[" << client->GetID() << "]: Server recived: ";
            std::cout << msg.body <<std::endl;
            // Simply bounce message back to client
            Networking::Message<CustomMsgTypes> msgToSend;
            msgToSend.header.id = CustomMsgTypes::ProbeMatch;
            msgToSend << PrepareProbeMatchMessage().data();
            client->Send(msgToSend);
        }
        break;

        case CustomMsgTypes::GetDataBase:
        {
            std::cout << "[" << client->GetID() << "]: Server recived: ";
            std::cout << msg.body <<std::endl;
            // Simply bounce message back to client
            Networking::Message<CustomMsgTypes> msgToSend;
            msgToSend.header.id = CustomMsgTypes::GetDataBaseResponse;
            msgToSend << PrepareGetDataBaseResponseMessage().data();
            client->Send(msgToSend);
        }
        break;

        case CustomMsgTypes::Subscribe:
        {
            std::cout << "[" << client->GetID() << "]: Server recived: ";
            std::cout << msg.body <<std::endl;
            // Simply bounce message back to client
            Networking::Message<CustomMsgTypes> msgToSend;
            msgToSend.header.id = CustomMsgTypes::SubscribeResponse;
            msgToSend << PrepareSubscribeResponseMessage().data();
            client->Send(msgToSend);
        }
        break;

        case CustomMsgTypes::StartReports:
        {
            std::cout << "[" << client->GetID() << "]: Server recived: ";
            std::cout << msg.body <<std::endl;
            Networking::Message<CustomMsgTypes> reportAToSend;
            reportAToSend.header.id = CustomMsgTypes::ReportTypeA;
            reportAToSend << reportA;
            client->Send(reportAToSend);
        }
        break;

        case CustomMsgTypes::ReportTypeAresponse:
        {
            static int reportACounter{0};
            std::cout << "[" << client->GetID() << "]: Server recived: ";
            std::cout << msg.body <<std::endl;
            // Simply bounce message back to client
            if(reportACounter<5)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                Networking::Message<CustomMsgTypes> msgToSend;
                msgToSend.header.id = CustomMsgTypes::ReportTypeA;
                msgToSend << reportA;
                client->Send(msgToSend);
                reportACounter++;
            } else {
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                Networking::Message<CustomMsgTypes> msgToSend;
                msgToSend.header.id = CustomMsgTypes::ReportTypeB;
                msgToSend << reportB;
                client->Send(msgToSend);
            }
        }
        break;

        case CustomMsgTypes::ReportTypeBresponse:
        {
            static int reportBcounter{1};
            std::cout << "[" << client->GetID() << "]: Server recived: ";
            std::cout << msg.body <<std::endl;
            if(reportBcounter<5)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                Networking::Message<CustomMsgTypes> msgToSend;
                msgToSend.header.id = CustomMsgTypes::ReportTypeB;
                msgToSend << reportB;
                client->Send(msgToSend);
                reportBcounter++;
            } else {
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                Networking::Message<CustomMsgTypes> msg;
                msg.header.id = CustomMsgTypes::StoppingReports;
                msg << PrepareStoppingReportsMessage().data();
                client->Send(msg);
            }
        }
        break;

        case CustomMsgTypes::SetCommandOne:
        {
            std::cout << "[" << client->GetID() << "]: Server recived: ";
            std::cout << msg.body <<std::endl;
            Networking::Message<CustomMsgTypes> msg;
            msg.header.id = CustomMsgTypes::SetCommandOneResponse;
            msg << setOneResponse;
            client->Send(msg);
        }
        break;

        case CustomMsgTypes::SetCommandTwo:
        {
            std::cout << "[" << client->GetID() << "]: Server recived: ";
            std::cout << msg.body <<std::endl;
            Networking::Message<CustomMsgTypes> msg;
            msg.header.id = CustomMsgTypes::SetCommandTwoResponse;
            msg << setTwoResponse;
            client->Send(msg);
        }
        break;

        case CustomMsgTypes::GracefullyDisconnect:
        {
            std::cout << "[" << client->GetID() << "]: Server recived: ";
            std::cout << msg.body <<std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            client->Disconnect();
        }
        break;
        }
    }
};

} // ApplicationLogic
