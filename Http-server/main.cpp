#include <iostream>
#include "Networking/Server.h"

class CustomServer : public Networking::Server{
public:
    CustomServer(uint16_t port) : Networking::Server(port){}
protected:
    virtual bool OnClientConnect(std::shared_ptr<Networking::Connection> client)
    {
        std::cout<<"On client Connect function. \n";
        return true;
    }

    // Called when a client appears to have disconnected
    virtual void OnClientDisconnect(std::shared_ptr<Networking::Connection> client)
    {
        std::cout << "Removing client [" << client->GetID() << "]\n";
    }
};

int main()
{
    CustomServer server(60000);
    server.Start();

    while (1)
    {
        server.Update(-1, true);
    }

    return 0;
}
