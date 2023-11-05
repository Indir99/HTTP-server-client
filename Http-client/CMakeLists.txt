cmake_minimum_required(VERSION 3.5)

project(Http-client LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the include directories for libasio
include_directories(/usr/include/asio)

add_executable(Http-client main.cpp)

install(TARGETS Http-client
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

