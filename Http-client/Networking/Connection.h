#pragma once

#include<memory>
#include<asio/ip/tcp.hpp>
#include"../Utilities/ThreadSafeQueue.h"
#include<asio/connect.hpp>


namespace Networking{

class Connection : std::enable_shared_from_this<Connection>{
public:

    // A connection is "owned" by either a server or a client, and its
    // behaviour is slightly different bewteen the two.
    enum class owner
    {
        server,
        client
    };

    // Constructor: Specify Owner, connect to context, transfer the socket
    //				Provide reference to incoming message queue
    Connection(owner parent, asio::io_context& asioContext, asio::ip::tcp::socket socket, Utilities::ThreadSafeQueue<std::string>& qIn)
        : m_asioContext(asioContext), m_socket(std::move(socket)), m_qMessagesIn(qIn){
        m_nOwnerType = parent;
    }

    virtual ~Connection(){}

    // This ID is used system wide - its how clients will understand other clients
    // exist across the whole system.
    uint32_t GetID() const
    {
        return id;
    }

public:
    void ConnectToClient(uint32_t uid = 0) {
        if (m_nOwnerType == owner::server) {
            if (m_socket.is_open()) {
                id = uid;
                //ReadHeader();
            }
        }
    }

    void ConnectToServer(const asio::ip::tcp::resolver::results_type& endpoints) {
        // Only clients can connect to servers
        if (m_nOwnerType == owner::client)
        {
            // Request asio attempts to connect to an endpoint
            asio::async_connect(m_socket, endpoints,
                                [this](std::error_code ec, asio::ip::tcp::endpoint endpoint)
                                {
                                    if (!ec)
                                    {
                                        //ReadHeader();
                                    }
                                });
        }
    }

    void Disconnect(){
        if (IsConnected())
            asio::post(m_asioContext, [this]() { m_socket.close(); });
    }

    bool IsConnected() const {
        return m_socket.is_open();
    }

public:
    // ASYNC - Send a message, connections are one-to-one so no need to specifiy
    // the target, for a client, the target is the server and vice versa
    void Send(const std::string& msg)
    {
        asio::post(m_asioContext,
                   [this, msg]()
                   {
                       // If the queue has a message in it, then we must
                       // assume that it is in the process of asynchronously being written.
                       // Either way add the message to the queue to be output. If no messages
                       // were available to be written, then start the process of writing the
                       // message at the front of the queue.
                       bool bWritingMessage = !m_qMessagesOut.empty();
                       m_qMessagesOut.push_back(msg);
                       if (!bWritingMessage)
                       {
                           //WriteHeader();
                       }
                   });
    }

private:

protected:
    // Each connection has a unique socket to a remote
    asio::ip::tcp::socket m_socket;

    // This context is shared with the whole asio instance
    asio::io_context& m_asioContext;

    // This queue holds all messages to be sent to the remote side
    // of this connection
    Utilities::ThreadSafeQueue<std::string> m_qMessagesOut;

    // This queue holds all messages that have been received from the
    // remote side of the connection. Note it is a reference as the
    // "owner" of this connection is expected to provide a Queue
    Utilities::ThreadSafeQueue<std::string>& m_qMessagesIn;

    // Incoming messages are constructed asynchronously, so we will
    // store the part assembled message here, until it is ready
    std::string m_msgTemporaryIn;

    // The "owner" decides how some of the connection behaves
    owner m_nOwnerType = owner::server;

    uint32_t id = 0;

};

} // Networking
