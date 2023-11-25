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
                }
                break;

                case ApplicationLogic::CustomMsgTypes::ReportTypeAresponse:
                {
                    // Server has responded to a ping request
                    std::cout<<"ReportA: "<< msg.body << std::endl;
                    c.ReportTypeAresponse();
                }
                break;

                case ApplicationLogic::CustomMsgTypes::ReportTypeBresponse:
                {
                    // Server has responded to a ping request
                    std::cout<<"ReportB: "<< msg.body << std::endl;
                    c.ReportTypeBresponse();
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
