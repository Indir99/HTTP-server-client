#include "../Networking/Message.h"
#include "../Networking/Connection.h"
#include "../Networking/Server.h"

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
    StoppingReports
};

constexpr char hello[]{"Hello from Server"};
constexpr char probeMatch[]{"ProbeMatch from Server"};
constexpr char getDataBaseResponse[]{"DataBase data from Server"};
constexpr char subscribeResponse[]{"SubscribeResponse from Server"};
constexpr char unsubscribeResponse[]{"UnsubscribeResponse from Server"};
constexpr char reportA[]{"Report typr A from Server"};
constexpr char reportB[]{"Report typr B from Server"};
constexpr char stoppingReports[]{"Reports sent sucessfully!"};


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
            msgToSend << hello;
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
            msgToSend << probeMatch;
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
            msgToSend << getDataBaseResponse;
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
            msgToSend << subscribeResponse;
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

        case CustomMsgTypes::ReportTypeAresponse:
        {
            static int reportACounter{0};
            std::cout << "[" << client->GetID() << "]: Server recived: ";
            std::cout << msg.body <<std::endl;
            // Simply bounce message back to client
            if(reportACounter<5)
            {
                Networking::Message<CustomMsgTypes> msgToSend;
                msgToSend.header.id = CustomMsgTypes::ReportTypeA;
                msgToSend << reportA;
                client->Send(msgToSend);
                reportACounter++;
            } else {
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
                // Simply bounce message back to client
                Networking::Message<CustomMsgTypes> msgToSend;
                msgToSend.header.id = CustomMsgTypes::ReportTypeB;
                msgToSend << reportB;
                client->Send(msgToSend);
                reportBcounter++;
            } else {
                Networking::Message<CustomMsgTypes> msg;
                msg.header.id = CustomMsgTypes::StoppingReports;
                msg << stoppingReports;
                client->Send(msg);
            }
        }
        break;
        }
    }
};

} // ApplicationLogic
