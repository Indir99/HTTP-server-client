#include <iostream>
#include "Networking/Client.h"

class CustomClient : public Networking::Client{
public:
    void PingServer()
    {
    }

    void MessageAll()
    {
    }
};

int main()
{
    CustomClient c;
    bool isConnected{c.Connect("127.0.0.1", 60000)};
    if(isConnected){
        std::cout<<"successfully connected. \n";
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        c.Disconnet();
    } else {
        std::cout<<"Connection error. \n";
    }
    std::cout<<"Finishing app \n";
    return 0;
}
