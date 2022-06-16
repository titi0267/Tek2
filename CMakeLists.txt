cmake_minimum_required(VERSION 3.12)

project(bomberman CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_CXX_FLAGS "-g")
include("${CMAKE_SOURCE_DIR}/cmake/Findraylib.cmake")
find_package(raylib REQUIRED)

add_executable(bomberman
    "src/main.cpp"

    "src/ecs/engine/World.cpp"
    "src/ecs/engine/SceneManager.cpp"

    "src/Map.cpp"

    "src/ecs/systems/ClickUpdate.cpp"
    "src/ecs/systems/DrawCube.cpp"
    "src/ecs/systems/DrawModel.cpp"
    "src/ecs/systems/Hoverable.cpp"
    "src/ecs/systems/KeyRecorder.cpp"
    "src/ecs/systems/Text3D.cpp"
    "src/ecs/systems/TextInput.cpp"
    "src/ecs/systems/SceneMoveElement.cpp"
    "src/ecs/systems/Button.cpp"

    "src/input/GamepadBind.cpp"
    "src/input/GamepadMap.cpp"
    "src/input/InputFile.cpp"
    "src/input/KeyboardBind.cpp"
    "src/input/KeyboardMap.cpp"

    "src/scenes/MainMenuScene.cpp"
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
