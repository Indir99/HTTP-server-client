#pragma once

#include "Connection.h"
#include "../Utilities/ThreadSafeQueue.h"
#include <memory>
#include <asio/ip/tcp.hpp>
#include <thread>
#include <iterator>
#include <algorithm>

namespace Networking{

class Server{
public:
    Server(uint16_t port) :
        m_asioAcceptor(m_asioContext, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)){}
    virtual ~Server(){
        Stop();
    }

    bool Start(){
        try{
            WaitForClientConnection();
            m_threadContext = std::thread([this](){ m_asioContext.run();});
        } catch (std::exception& ex) {
            // Something prohabited server from listening
            std::cerr << "[SERVER] Exception: "<< ex.what() << "\n";
            return false;
        }
        std::cout<< "[SERVER] started!\n";
        return true;
    }
    void Stop(){
        // Request the context to close
        m_asioContext.stop();
        // Tidy up the context thread
        if(m_threadContext.joinable()){
            m_threadContext.join();
        }

        std::cout<< "[SERVER] Stopped\n";
    }

    // ASYNC - Instruct asio to wait for connection
    void WaitForClientConnection(){
        m_asioAcceptor.async_accept(
            [this](std::error_code ec, asio::ip::tcp::socket socket){
                if(!ec){
                    std::cout<< "[SERVER] New connection: "<< socket.remote_endpoint() <<"\n";

                    std::shared_ptr<Connection> newconn = std::make_shared<Connection>(Connection::owner::server, m_asioContext, std::move(socket), m_qMessageIn);

                    // Give the user server chance to deny connection
                    if(OnClientConnect(newconn)){
                        // Connection allowed, so add to containter of new connections
                        m_deqConnections.push_back(std::move(newconn));
                        // Give an ID
                        m_deqConnections.back()->ConnectToClient(nIDCounter++);
                        std::cout<<"["<<m_deqConnections.back()->GetID()<<"] Connection Approved\n";

                    } else {
                        std::cout<< "[-----] Connection Denided\n";
                    }

                } else {
                    // Error has occured during acceptance
                    std::cout << "[SERVER] New connection error: "<< ec.message() <<"\n";
                }

                // Prime asio context with more work - again simply wait for
                // another connection
                WaitForClientConnection();
            });
    }

    void MessageClient(std::shared_ptr<Connection> client, std::string& msg){
        if(client && client->IsConnected()) {
            client->Send(msg);
        } else {
            OnClientDisconnect(client);
            client.reset();
            m_deqConnections.erase(std::remove(m_deqConnections.begin(), m_deqConnections.end(), client), m_deqConnections.end());
        }
    }

    // Send Message to all clients
    void MessageAllClients(const std::string& msg, std::shared_ptr<Connection> pIgnoreClient = nullptr){}

protected:
    // Called when a client connects, you can veto connection by returning false
    virtual bool OnClientConnect(std::shared_ptr<Connection> client){}

    // Called when client apeears to have disconnected
    virtual void OnClientDisconnect(std::shared_ptr<Connection> client){}

    // Called when message arrives
    virtual void OnMessage(std::shared_ptr<Connection> client, std::string msg){}
protected:
    // Thread Safe Queue for incoming message packets
    Utilities::ThreadSafeQueue<std::string> m_qMessageIn;
    // Container of active validated connection
    std::deque<std::shared_ptr<Connection>> m_deqConnections;
    // Order of declaration is important - it is also oreder for initialization
    asio::io_context m_asioContext;
    std::thread m_threadContext;

    // These things need an asio context
    asio::ip::tcp::acceptor m_asioAcceptor;

    // Client would be identified in the "wider system" via an ID
    uint32_t nIDCounter = 10000;
};

} // Networking
