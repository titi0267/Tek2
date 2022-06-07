cmake_minimum_required(VERSION 3.12)

project(indiestudio CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
include("${CMAKE_SOURCE_DIR}/cmake/Findraylib.cmake")
find_package(raylib REQUIRED)

add_executable(indiestudio
    "src/main.cpp"

    "src/ecs/World.cpp"

    "src/ecs/systems/ClickUpdate.cpp"
    "src/ecs/systems/DrawCube.cpp"
    "src/ecs/systems/DrawModel.cpp"
    "src/ecs/systems/Hoverable.cpp"
    "src/ecs/systems/Text3D.cpp"

    "src/network/client/LinuxClient.cpp"
    "src/network/client/WinClient.cpp"
    "src/network/server/LinuxServer.cpp"
    "src/network/server/WinServer.cpp"
    "src/network/sockets/CPSocket.cpp"
    "src/network/sockets/SocketError.cpp"
    "src/network/sockets/LinuxSocket.cpp"
    "src/network/sockets/WinSocket.cpp"
)

target_link_libraries(indiestudio raylib)
target_include_directories(indiestudio
    PRIVATE
        "${CMAKE_SOURCE_DIR}/include"
        "${raylib_SOURCE_DIR}/"
)
set_target_properties(indiestudio
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/"
)
