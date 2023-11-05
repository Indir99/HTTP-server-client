#pragma once

#include "../Utilities/ThreadSafeQueue.h"
#include "Connection.h"
#include<asio/ip/tcp.hpp>
#include<thread>
#include<memory>


namespace Networking{
class Client {
public:

    // Initialize the socket with io context, so it can do stuff
    Client() : m_socket(m_context){}

    // If the client is destroyed, always try and disconnet from server
    virtual ~Client(){ Disconnet();}

    // Connect to server with hostname/ip_address and port
    bool Connect(const std::string& host, const uint16_t port)
    {
        try {
            // Create connection
            m_connection = std::make_unique<Connection>(); //TODO
            asio::ip::tcp::resolver resolver(m_context);
            // Resolve hostname/ip_address into tangiable physical address
            auto m_endpoits = resolver.resolve(host, std::to_string(port));
            m_connection->ConnectToServer(m_endpoints);

            thrContext = std::thread([this](){m_context.run();});

        } catch (std::exception& ex) {
            std::cerr << "Client Exception: "<< ex.what() << "\n";
            return false;
        }
    }

    // Disconnect from server
    void Disconnet(){}

    // Check if Client is actually connteted to server
    bool IsConnected(){
        if(m_connection){
            return m_connection->IsConnected();
        }else {
            return false;
        }
    }

    //Retreive Queue of messages from server
    Utilities::ThreadSafeQueue<std::string>& Incoming()
    {
        return m_qMessagesIn;
    }

protected:
    // asio context handle the data transfer
    asio::io_context m_context;
    // but need a thread of its own to execute its work commands
    std::thread thrContext;
    // This is a hardware socket that is connected to server
    asio::ip::tcp::socket m_socket;
    // The client has a single instance of "Connection" object which handles the data transfer
    std::unique_ptr<Connection> m_connection;

 private:
    // This is thread safe queue of incoming messages from server
    Utilities::ThreadSafeQueue<std::string> m_qMessagesIn;
};
} // Networking
