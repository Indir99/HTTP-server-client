cmake_minimum_required(VERSION 3.5)

project(Http-server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the include directories for libasio
include_directories(/usr/include/asio)

add_subdirectory(Utilities)
add_subdirectory(Networking)


add_executable(Http-server main.cpp)

target_link_libraries(Http-server PRIVATE Utilities Networking)

install(TARGETS Http-server
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
