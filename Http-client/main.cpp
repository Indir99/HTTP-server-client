#include <iostream>
#include "Networking/Client.h"

enum class CustomMsgTypes : uint32_t
{
    ServerAccept,
    ServerDeny,
    ServerPing,
    MessageAll,
    ServerMessage,
};


class CustomClient : public Networking::ClientInterface<CustomMsgTypes>
{
public:
    void PingServer()
    {
        Networking::Message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::ServerPing;

        // Caution with this...
        std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();

        msg << timeNow;
        Send(msg);
    }

    void MessageAll()
    {
        Networking::Message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::MessageAll;
        Send(msg);
    }
};

int main()
{
    CustomClient c;
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
                case CustomMsgTypes::ServerAccept:
                {
                    // Server has responded to a ping request
                    std::cout << "Server Accepted Connection\n";
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    c.PingServer();
                }
                break;


                case CustomMsgTypes::ServerPing:
                {
                    // Server has responded to a ping request
                    std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
                    std::chrono::system_clock::time_point timeThen;
                    msg >> timeThen;
                    std::cout << "Ping: " << std::chrono::duration<double>(timeNow - timeThen).count() << "\n";
                    c.MessageAll();
                }
                break;

                case CustomMsgTypes::ServerMessage:
                {
                    // Server has responded to a ping request
                    uint32_t clientID;
                    msg >> clientID;
                    std::cout << "Hello from [" << clientID << "]\n";
                }
                break;
                }
            }
        }
        else
        {
            std::cout << "Server Down\n";
            bQuit = true;
        }

    }

    return 0;
}
