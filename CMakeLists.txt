cmake_minimum_required(VERSION 3.12)

project(bomberman CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
include("${CMAKE_SOURCE_DIR}/cmake/Findraylib.cmake")
find_package(raylib REQUIRED)

add_executable(bomberman
    "src/main.cpp"

    "src/ecs/engine/World.cpp"
    "src/ecs/engine/SceneManager.cpp"

    "src/ecs/systems/ClickUpdate.cpp"
    "src/ecs/systems/DrawCube.cpp"
    "src/ecs/systems/DrawModel.cpp"
    "src/ecs/systems/Hoverable.cpp"
    "src/ecs/systems/Text3D.cpp"
    "src/ecs/systems/SceneMoveElement.cpp"
    "src/ecs/systems/Button.cpp"

    "src/scenes/MainMenuScene.cpp"
)

target_link_libraries(bomberman raylib)
target_include_directories(bomberman
    PRIVATE
        "${CMAKE_SOURCE_DIR}/include"
        "${raylib_SOURCE_DIR}/"
)
set_target_properties(bomberman
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/"
)
