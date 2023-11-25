#pragma once

#include <memory>
#include <thread>
#include <mutex>
#include <deque>
#include <optional>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

namespace Networking
{

// Message Header is sent at start of all messages. The template allows us
// to use "enum class" to ensure that the messages are valid at compile time
template <typename T>
struct MessageHeader
{
    T id{};
    uint32_t size = 0;
};

// Message Body contains a header and a std::vector, containing raw bytes
// of infomation. This way the message can be variable length, but the size
// in the header must be updated.
template <typename T>
struct Message
{
    // Header & Body vector
    MessageHeader<T> header{};
    //std::vector<uint8_t> body;
    std::string body;

    // returns size of entire message packet in bytes
    size_t size() const
    {
        return body.size();
    }

    // Override for std::cout compatibility - produces friendly description of message
    friend std::ostream& operator << (std::ostream& os, const Message<T>& msg)
    {
        os << "ID:" << int(msg.header.id) << " Size:" << msg.header.size;
        return os;
    }

    // Convenience Operator overloads
    friend Message<T>& operator << (Message<T>& msg, const char* data)
    {
        msg.body = data;
        // Recalculate the message size
        msg.header.size = msg.size();
        // Return the target message so it can be "chained"
        return msg;
    }
};


// An "owned" message is identical to a regular message, but it is associated with
// a connection. On a server, the owner would be the client that sent the message,
// on a client the owner would be the server.

// Forward declare the connection
template <typename T>
class Connection;

template <typename T>
struct OwnedMessage
{
    std::shared_ptr<Connection<T>> remote = nullptr;
    Message<T> msg;

    // Again, a friendly string maker
    friend std::ostream& operator<<(std::ostream& os, const OwnedMessage<T>& msg)
    {
        os << msg.msg;
        return os;
    }
};

} // Networking
