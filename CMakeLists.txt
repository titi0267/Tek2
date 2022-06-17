cmake_minimum_required(VERSION 3.12)

project(bomberman CXX)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
include("${CMAKE_SOURCE_DIR}/cmake/Findraylib.cmake")
find_package(raylib REQUIRED)

add_executable(bomberman
    "src/main.cpp"
    "src/Setup.cpp"
    "src/Assets.cpp"

    "src/Map.cpp"

    "src/ecs/engine/World.cpp"
    "src/ecs/engine/Network.cpp"
    "src/ecs/engine/ClientManager.cpp"
    "src/ecs/engine/ServerManager.cpp"
    "src/ecs/engine/SceneManager.cpp"
    "src/ecs/engine/PlayersManager.cpp"
    "src/ecs/engine/InternalServer.cpp"

    "src/ecs/systems/ClickUpdate.cpp"
    "src/ecs/systems/DrawCube.cpp"
    "src/ecs/systems/DrawModel.cpp"
    "src/ecs/systems/Hoverable.cpp"
    "src/ecs/systems/Text3D.cpp"
    "src/ecs/systems/SceneMoveElement.cpp"
    "src/ecs/systems/PlayerInputs.cpp"
    "src/ecs/systems/Movement.cpp"
    "src/ecs/systems/Bomb.cpp"
    "src/ecs/systems/Timer.cpp"
    "src/ecs/systems/Water.cpp"
    "src/ecs/systems/SpawnBonus.cpp"
    "src/ecs/systems/Animation.cpp"
    "src/ecs/systems/LobbyActions.cpp"
    "src/ecs/systems/GameActions.cpp"
    "src/ecs/systems/BackgroundRotation.cpp"
    "src/ecs/systems/CheckWin.cpp"

    "src/scenes/SceneList.cpp"
    "src/scenes/MainMenuScene.cpp"
    "src/scenes/GameScene.cpp"
    "src/scenes/GameServerScene.cpp"
    "src/scenes/LobbyServerScene.cpp"
    "src/scenes/WinServerScene.cpp"

    "src/network/client/LinuxClient.cpp"
    "src/network/client/WinClient.cpp"
    "src/network/server/LinuxServer.cpp"
    "src/network/server/WinServer.cpp"
    "src/network/sockets/CPSocket.cpp"
    "src/network/sockets/SocketError.cpp"
    "src/network/sockets/LinuxSocket.cpp"
    "src/network/sockets/WinSocket.cpp"
)

target_link_libraries(bomberman raylib)
target_include_directories(bomberman
    PRIVATE
        "${CMAKE_SOURCE_DIR}/include"
)
set_target_properties(bomberman
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/"
)
