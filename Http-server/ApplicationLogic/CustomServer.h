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
    UnsubscribeResponse,
    ReportTypeA,
    ReportTypeAresponse,
    ReportTypeB,
    ReportTypeBresponse
};

constexpr char hello[]{"Hello from Server"};
constexpr char probeMatch[]{"ProbeMatch from Server"};
constexpr char getDataBaseResponse[]{"DataBase data from Server"};
constexpr char subscribeResponse[]{"SubscribeResponse from Server"};
constexpr char unsubscribeResponse[]{"UnsubscribeResponse from Server"};
constexpr char reportA[]{"Report typr A from Server"};
constexpr char reportB[]{"Report typr B from Server"};


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

            //wait for 2 secs
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            Networking::Message<CustomMsgTypes> reportAToSend;
            msgToSend.header.id = CustomMsgTypes::ReportTypeA;
            msgToSend << reportA;
            client->Send(reportAToSend);

        }
        break;

        case CustomMsgTypes::ReportTypeAresponse:
        {
            std::cout << "[" << client->GetID() << "]: Server recived: ";
            std::cout << msg.body <<std::endl;
            // Simply bounce message back to client
            Networking::Message<CustomMsgTypes> msgToSend;
            msgToSend.header.id = CustomMsgTypes::ReportTypeB;
            msgToSend << reportB;
            client->Send(msgToSend);
        }
        break;
        }
    }
};

} // ApplicationLogic
