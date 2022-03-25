cmake_minimum_required(VERSION 3.17)

project(arcade)

set(SRCS
    Source/Main.cpp
    Source/Error/Error.cpp
    Source/DlLib.cpp
    )

set(HEADERS
    arcade-interface-master/ICore.hpp
    arcade-interface-master/IDisplayModule.hpp
    arcade-interface-master/IGameModule.hpp
    Source/Error/Error.hpp
    Source/define.hpp
    Source/DlLib.hpp
    )

add_executable(arcade ${SRCS} ${HEADERS})
target_link_libraries(arcade dl)
