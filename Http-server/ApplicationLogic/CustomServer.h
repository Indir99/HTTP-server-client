#include "../Networking/Message.h"
#include "../Networking/Connection.h"
#include "../Networking/Server.h"
#include "SoapMessageCreator.h"
#include "XmlParser.h"

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
            std::cout << "[" << client->GetID() << "]: Server recived: Hello message. Client registred with id: " << client->GetID() <<std::endl;
            std::cout<<"Content of Hello message: " << msg.body << std::endl;
            // Simply bounce message back to client
            Networking::Message<CustomMsgTypes> msgToSend;
            msgToSend.header.id = CustomMsgTypes::Hello;
            msgToSend << PrepareHelloMessage().data();
            client->Send(msgToSend);
        }
        break;

        case CustomMsgTypes::Probe:
        {
            std::cout << "[" << client->GetID() << "]: Server recived: Probe message."<<std::endl;
            std::cout<<"Message content: "<<std::endl;
            XmlParser parser;
            parser.ParseMessage(msg.body);
            ProbeData probe;
            parser.GetProbeData(probe);
            probe.print();
            // Simply bounce message back to client
            Networking::Message<CustomMsgTypes> msgToSend;
            msgToSend.header.id = CustomMsgTypes::ProbeMatch;
            msgToSend << PrepareProbeMatchMessage().data();
            client->Send(msgToSend);
        }
        break;

        case CustomMsgTypes::GetDataBase:
        {
            std::cout << "[" << client->GetID() << "]: Server recived: GetDataBase message."<<std::endl;
            std::cout<<"Message content: "<<std::endl;
            XmlParser parser;
            parser.ParseMessage(msg.body);;
            DatabaseData db;
            parser.GetDataBaseData(db);
            db.print();
            // Simply bounce message back to client
            Networking::Message<CustomMsgTypes> msgToSend;
            msgToSend.header.id = CustomMsgTypes::GetDataBaseResponse;
            msgToSend << PrepareGetDataBaseResponseMessage().data();
            client->Send(msgToSend);
        }
        break;

        case CustomMsgTypes::Subscribe:
        {
            std::cout << "[" << client->GetID() << "]: Server recived: Subscribe message."<<std::endl;
            std::cout<<"Message content: "<<std::endl;
            XmlParser parser;
            parser.ParseMessage(msg.body);
            SubscribeData subs;
            parser.GetSubscribeData(subs);
            subs.print();
            // Simply bounce message back to client
            Networking::Message<CustomMsgTypes> msgToSend;
            msgToSend.header.id = CustomMsgTypes::SubscribeResponse;
            msgToSend << PrepareSubscribeResponseMessage().data();
            client->Send(msgToSend);
        }
        break;

        case CustomMsgTypes::StartReports:
        {
            std::cout << "[" << client->GetID() << "]: Server recived: StartReportsMessage."<<std::endl;
            std::cout<<"Message content: "<<std::endl;
            XmlParser parser;
            parser.ParseMessage(msg.body);
            StartReportsData repData;
            parser.GetStartReportsData(repData);
            repData.print();
            Networking::Message<CustomMsgTypes> reportAToSend;
            reportAToSend.header.id = CustomMsgTypes::ReportTypeA;
            reportAToSend << PrepareReportTypeAmessage("1234","Name","LastName","bloodPressure","38.6","200/100").data();
            client->Send(reportAToSend);
        }
        break;

        case CustomMsgTypes::ReportTypeAresponse:
        {
            static int reportACounter{0};
            std::cout << "[" << client->GetID() << "]: Server recived: ReportTypeAresponse message."<<std::endl;
            std::cout<<"Message content: "<<std::endl;
            XmlParser parser;
            parser.ParseMessage(msg.body);
            ReportTypeAdata data;
            parser.ReportTypeAresponseData(data);
            data.print();
            // Simply bounce message back to client
            if(reportACounter<5)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                Networking::Message<CustomMsgTypes> msgToSend;
                msgToSend.header.id = CustomMsgTypes::ReportTypeA;
                msgToSend << PrepareReportTypeAmessage("1234","Name","LastName","bloodPressure","38.6","200/100").data();
                client->Send(msgToSend);
                reportACounter++;
            } else {
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                Networking::Message<CustomMsgTypes> msgToSend;
                msgToSend.header.id = CustomMsgTypes::ReportTypeB;
                msgToSend << PrepareReportTypeBmessage("1234","Name","LastName","3333", "doctorName","doctorLastName", "therapyName", "STARTED").data();
                client->Send(msgToSend);
            }
        }
        break;

        case CustomMsgTypes::ReportTypeBresponse:
        {
            static int reportBcounter{1};
            std::cout << "[" << client->GetID() << "]: Server recived: ReportTypeBresponse message."<<std::endl;
            std::cout<<"Message content: "<<std::endl;
            XmlParser parser;
            parser.ParseMessage(msg.body);
            ReportTypeBdata data;
            parser.ReportTypeBresponseData(data);
            data.print();
            if(reportBcounter<5)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                Networking::Message<CustomMsgTypes> msgToSend;
                msgToSend.header.id = CustomMsgTypes::ReportTypeB;
                msgToSend << PrepareReportTypeBmessage("1234","Name","LastName","3333", "doctorName","doctorLastName", "therapyName", "STARTED").data();;
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
            std::cout << "[" << client->GetID() << "]: Server recived: SetCommandOne message."<<std::endl;;
            std::cout<<"Message content: "<<std::endl;
            XmlParser parser;
            parser.ParseMessage(msg.body);
            //parser.PrintParsedElements();
            SetCommandOneData data;
            parser.GetCommandOneData(data);
            data.print();
            Networking::Message<CustomMsgTypes> msg;
            msg.header.id = CustomMsgTypes::SetCommandOneResponse;
            msg << PrepareSetCommandOneResponseMessage().data();
            client->Send(msg);
        }
        break;

        case CustomMsgTypes::SetCommandTwo:
        {
            std::cout << "[" << client->GetID() << "]: Server recived: SetCommandTwo message."<<std::endl;
            std::cout<<"Message content: "<<std::endl;
            XmlParser parser;
            parser.ParseMessage(msg.body);
            //parser.PrintParsedElements();
            SetCommandTwoData data;
            parser.GetCommandTwoData(data);
            data.print();
            Networking::Message<CustomMsgTypes> msg;
            msg.header.id = CustomMsgTypes::SetCommandTwoResponse;
            msg << PrepareSetCommandTwoResponseMessage().data();
            client->Send(msg);
        }
        break;

        case CustomMsgTypes::GracefullyDisconnect:
        {
            std::cout << "[" << client->GetID() << "]: Server recived: Bye message.";
            std::cout << msg.body <<std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            client->Disconnect();
        }
        break;
        }
    }
};

} // ApplicationLogic
