#include <iostream>
#include "ApplicationLogic/CustomClient.h"
#include "ApplicationLogic/SoapMessageCreator.h"
#include "ApplicationLogic/XmlParser.h"

int main()
{
    ApplicationLogic::InitializeLibrary();
    ApplicationLogic::CustomClient c;
    c.Connect("127.0.0.1", 60000);
    bool bQuit{true};
    while (bQuit)
    {
        if (c.IsConnected())
        {
            if (!c.Incoming().empty())
            {
                auto msg = c.Incoming().pop_front().msg;

                switch (msg.header.id)
                {
                case ApplicationLogic::CustomMsgTypes::ServerAccept:
                {
                    // Server has responded to a ping request
                    std::cout << "Server Accepted Connection\n";
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    c.Hello();
                }
                break;


                case ApplicationLogic::CustomMsgTypes::Hello:
                {
                    // Server has responded to a ping request
                    std::cout<<"Hello response: "<< msg.body << std::endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    c.Probe();
                }
                break;

                case ApplicationLogic::CustomMsgTypes::ProbeMatch:
                {
                    // Server has responded to a ping request
                    std::cout<<"Probe response: "<<std::endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    ApplicationLogic::XmlParser parser;
                    parser.ParseMessage(msg.body);
                    ProbeMatchData probe;
                    parser.GetProbeMatchData(probe);
                    probe.print();
                    c.GetDataBase();
                }
                break;

                case ApplicationLogic::CustomMsgTypes::GetDataBaseResponse:
                {
                    // Server has responded to a ping request
                    std::cout<<"GetDataBase response: "<<std::endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    ApplicationLogic::XmlParser parser;
                    parser.ParseMessage(msg.body);
                    DatabaseResponseData db;
                    parser.GetDataBaseResponseData(db);
                    db.print();
                    c.Subscribe();
                }
                break;

                case ApplicationLogic::CustomMsgTypes::SubscribeResponse:
                {
                    // Server has responded to a ping request
                    std::cout<<"Subscribe response: "<<std::endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    ApplicationLogic::XmlParser parser;
                    parser.ParseMessage(msg.body);
                    SubscribResponseData subRe;
                    parser.GetSubscribeResponseData(subRe);
                    subRe.print();
                    c.StartReports();
                }
                break;

                case ApplicationLogic::CustomMsgTypes::ReportTypeA:
                {
                    // Server has responded to a ping request
                    std::cout<<"Report A:" <<std::endl;
                    ApplicationLogic::XmlParser parser;
                    parser.ParseMessage(msg.body);
                    ReportTypeAdata data;
                    parser.GetReportTypeAdata(data);
                    data.print();
                    c.ReportTypeAresponse();
                }
                break;

                case ApplicationLogic::CustomMsgTypes::ReportTypeB:
                {
                    // Server has responded to a ping request
                    std::cout<<"Report B:" <<std::endl;
                    ApplicationLogic::XmlParser parser;
                    parser.ParseMessage(msg.body);
                    ReportTypeBdata data;
                    parser.GetReportTypeBdata(data);
                    data.print();
                    c.ReportTypeBresponse();

                }
                break;

                case ApplicationLogic::CustomMsgTypes::StoppingReports:
                {
                    // Server has responded to a ping request
                    std::cout<<"Stopping message: "<<std::endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    ApplicationLogic::XmlParser parser;
                    parser.ParseMessage(msg.body);
                    StoppingReportsData stopp;
                    parser.GetStoppingReportsData(stopp);
                    stopp.print();
                    c.SetCommandOne();
                }
                break;

                case ApplicationLogic::CustomMsgTypes::SetCommandOneResponse:
                {
                    // Server has responded to a ping request
                    std::cout<<"Set Command ONE response: "<<std::endl;
                    ApplicationLogic::XmlParser parser;
                    parser.ParseMessage(msg.body);
                    //parser.PrintParsedElements();
                    SetCommandOneResponseData data;
                    parser.GetCommandOneResponseData(data);
                    data.print();
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    c.SetCommandTwo();
                }
                break;

                case ApplicationLogic::CustomMsgTypes::SetCommandTwoResponse:
                {
                    // Server has responded to a ping request
                    std::cout<<"Set command TWO response: "<< std::endl;
                    ApplicationLogic::XmlParser parser;
                    parser.ParseMessage(msg.body);
                    SetCommandTwoResponseData data;
                    parser.GetCommandTwoResponseData(data);
                    data.print();
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    c.GracefullyDisconnect();
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    c.Disconnect();
                }
                break;
                }
            }
        }
        else
        {
            std::cout << "Server Down\n";
            bQuit = false;
        }
    }
    ApplicationLogic::DeinitializeLibrary();

    return 0;
}
