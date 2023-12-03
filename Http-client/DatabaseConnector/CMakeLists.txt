# Set the source files in the current directory (folder with .h and .cpp files)
set(SOURCES
    DatabaseConnector.h
    DatabaseConnector.cpp
)

# Create a library or executable target for the source files
add_library(DatabaseConnector ${SOURCES})
