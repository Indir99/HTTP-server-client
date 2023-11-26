#include <iostream>
#include "ApplicationLogic/CustomClient.h"

int main()
{
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
                    std::cout<<"Probe response: "<< msg.body << std::endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    c.GetDataBase();
                }
                break;

                case ApplicationLogic::CustomMsgTypes::GetDataBaseResponse:
                {
                    // Server has responded to a ping request
                    std::cout<<"GetDataBase response: "<< msg.body << std::endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    c.Subscribe();
                }
                break;

                case ApplicationLogic::CustomMsgTypes::SubscribeResponse:
                {
                    // Server has responded to a ping request
                    std::cout<<"Subscribe response: "<< msg.body << std::endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    c.StartReports();
                }
                break;

                case ApplicationLogic::CustomMsgTypes::ReportTypeA:
                {
                    // Server has responded to a ping request
                    std::cout<<"ReportA: "<< msg.body << std::endl;
                    c.ReportTypeAresponse();
                }
                break;

                case ApplicationLogic::CustomMsgTypes::ReportTypeB:
                {
                    // Server has responded to a ping request
                    std::cout<<"ReportB: "<< msg.body << std::endl;
                    c.ReportTypeBresponse();
                }
                break;

                case ApplicationLogic::CustomMsgTypes::StoppingReports:
                {
                    // Server has responded to a ping request
                    std::cout<<"Stopping message: "<< msg.body << std::endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    c.SetCommandOne();
                }
                break;

                case ApplicationLogic::CustomMsgTypes::SetCommandOneResponse:
                {
                    // Server has responded to a ping request
                    std::cout<<"Set Command one response: "<< msg.body << std::endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    c.SetCommandTwo();
                }
                break;

                case ApplicationLogic::CustomMsgTypes::SetCommandTwoResponse:
                {
                    // Server has responded to a ping request
                    std::cout<<"Set command two response: "<< msg.body << std::endl;
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

    return 0;
}
