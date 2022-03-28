cmake_minimum_required(VERSION 3.17)

project(arcade)

set(SRCS
    Source/Main.cpp
    Source/Error/Error.cpp
    Source/DlLib.cpp
    Source/Games/Nibbler/Nibbler.cpp
    Source/Games/Pacman/Pacman.cpp
    Source/Graphical/nCurses/Ncurses.cpp
    Source/Graphical/Sdl2/Sdl2.cpp
    Source/Graphical/SFML/Sfml.cpp
    Source/Interface/Core.cpp
    Source/Interface/DisplayModule.cpp
    Source/Interface/GameModule.cpp
    )

set(HEADERS
    arcade-interface-master/ICore.hpp
    arcade-interface-master/IDisplayModule.hpp
    arcade-interface-master/IGameModule.hpp
    Source/Error/Error.hpp
    Source/define.hpp
    Source/DlLib.hpp
    Source/Games/Nibbler/Nibbler.hpp
    Source/Games/Pacman/Pacman.hpp
    Source/Graphical/nCurses/Ncurses.hpp
    Source/Graphical/Sdl2/Sdl2.hpp
    Source/Graphical/SFML/Sfml.hpp
    Source/Interface/Core.hpp
    Source/Interface/DisplayModule.hpp
    Source/Interface/GameModule.hpp
    )

add_executable(arcade ${SRCS} ${HEADERS})
target_link_libraries(arcade dl)
