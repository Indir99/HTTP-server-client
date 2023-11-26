# Set the source files in the current directory (folder with .h and .cpp files)
set(SOURCES
    CustomServer.h
    CustomServer.cpp
    SoapMessageCreator.h
    SoapMessageCreator.cpp
)

# Create a library or executable target for the source files
add_library(ApplicationLogic ${SOURCES})
