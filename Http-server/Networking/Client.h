#pragma once
#include "Message.h"
#include "Connection.h"

namespace Networking
{
template <typename T>
class ClientInterface
{
public:
    ClientInterface()
    {}

    virtual ~ClientInterface()
    {
        // If the client is destroyed, always try and disconnect from server
        Disconnect();
    }

public:
    // Connect to server with hostname/ip-address and port
    bool Connect(const std::string& host, const uint16_t port)
    {
        try
        {
            // Resolve hostname/ip-address into tangiable physical address
            asio::ip::tcp::resolver resolver(m_context);
            asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(host, std::to_string(port));

            // Create Connection
            m_Connection = std::make_unique<Connection<T>>(Connection<T>::owner::client, m_context, asio::ip::tcp::socket(m_context), m_qMessagesIn);

            // Tell the Connection object to connect to server
            m_Connection->ConnectToServer(endpoints);

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
    void Disconnect()
    {
        // If Connection exists, and it's connected then...
        if(IsConnected())
        {
            // ...disconnect from server gracefully
            m_Connection->Disconnect();
        }

        // Either way, we're also done with the asio context...
        m_context.stop();
        // ...and its thread
        if (thrContext.joinable())
            thrContext.join();

        // Destroy the Connection object
        m_Connection.release();
    }

    // Check if client is actually connected to a server
    bool IsConnected()
    {
        if (m_Connection)
            return m_Connection->IsConnected();
        else
            return false;
    }

public:
    // Send message to server
    void Send(const Message<T>& msg)
    {
        if (IsConnected())
            m_Connection->Send(msg);
    }

    // Retrieve queue of messages from server
    Utilities::ThreadSafeQueue<OwnedMessage<T>>& Incoming()
    {
        return m_qMessagesIn;
    }

protected:
    // asio context handles the data transfer...
    asio::io_context m_context;
    // ...but needs a thread of its own to execute its work commands
    std::thread thrContext;
    // The client has a single instance of a "Connection" object, which handles data transfer
    std::unique_ptr<Connection<T>> m_Connection;

private:
    // This is the thread safe queue of incoming messages from server
    Utilities::ThreadSafeQueue<OwnedMessage<T>> m_qMessagesIn;
};
}

