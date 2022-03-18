cmake_minimum_required(VERSION 3.17)

project(arcade)

set(SRCS
    Source/Main.cpp
    )

set(HEADERS
        arcade-interface-master/ICore.hpp
        arcade-interface-master/IDisplayModule.hpp
        arcade-interface-master/IGameModule.hpp
    )

add_executable(arcade ${SRCS} ${HEADERS})
