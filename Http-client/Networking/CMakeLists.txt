# Set the source files in the current directory (folder with .h and .cpp files)
set(SOURCES
    Connection.h
    Connection.cpp
    Server.h
    Server.cpp
    Client.h
    Client.cpp
)

# Create a library or executable target for the source files
add_library(Networking ${SOURCES})
