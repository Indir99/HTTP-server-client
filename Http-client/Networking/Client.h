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
    Client(){}

    // If the client is destroyed, always try and disconnet from server
    virtual ~Client(){ Disconnet();}

    // Connect to server with hostname/ip_address and port
    bool Connect(const std::string& host, const uint16_t port)
    {
        try
        {
            // Resolve hostname/ip-address into tangiable physical address
            asio::ip::tcp::resolver resolver(m_context);
            asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(host, std::to_string(port));
            // Create connection
            m_connection = std::make_unique<Connection>(Connection::owner::client, m_context, asio::ip::tcp::socket(m_context), m_qMessagesIn);

            // Tell the connection object to connect to server
            m_connection->ConnectToServer(endpoints);

            // Start Context Thread
            thrContext = std::thread([this]() { m_context.run(); });
        }
        catch (std::exception& e)
        {
            std::cerr << "Client Exception: " << e.what() << "\n";
            return false;
        }
        return true;
    }

    // Disconnect from server
    void Disconnet(){
        // If connection exists, and it's connected then ..
        if(IsConnected()) {
            // .. disconntect from server gracefully
        }
        // Either way, we are also done with the asio context
        m_context.stop();
        // .. and it's thread
        if(thrContext.joinable()){
            thrContext.join();
        }

        // Destroy the connectio object
        m_connection.release();
    }

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
    // The client has a single instance of "Connection" object which handles the data transfer
    std::unique_ptr<Connection> m_connection;

 private:
    // This is thread safe queue of incoming messages from server
    Utilities::ThreadSafeQueue<std::string> m_qMessagesIn;
};
} // Networking
