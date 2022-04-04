cmake_minimum_required(VERSION 3.17)

project(arcade)

set(SRCS
    Source/Main.cpp
    Source/Error/Error.cpp
    Source/DlLib.cpp
    Source/Games/Nibbler/Nibbler.cpp
    Source/Games/Pacman/Pacman.cpp
    Source/Interface/Core.cpp
    Source/Interface/DisplayModule.cpp
    Source/Interface/Texture.cpp
    )

set(SRCS_NCURSES
    Source/Graphical/nCurses/Ncurses.cpp
)

set(HEADERS_NCURSES
    arcade-interface-master/ICore.hpp
    arcade-interface-master/IDisplayModule.hpp
    arcade-interface-master/IGameModule.hpp
    Source/Error/Error.hpp
    Source/Graphical/nCurses/Ncurses.hpp
)

set(HEADERS_SFML
    arcade-interface-master/ICore.hpp
    arcade-interface-master/IDisplayModule.hpp
    arcade-interface-master/IGameModule.hpp
    Source/Error/Error.hpp
    Source/Graphical/SFML/Sfml.hpp
)

set(HEADERS_SDL2
    arcade-interface-master/ICore.hpp
    arcade-interface-master/IDisplayModule.hpp
    arcade-interface-master/IGameModule.hpp
    Source/Error/Error.hpp
    Source/Graphical/Sdl2/Sdl2.hpp
)

set(SRCS_SDL2
    Source/Graphical/Sdl2/Sdl2.cpp
)

set(SRCS_SFML
    Source/Graphical/SFML/Sfml.cpp
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
    Source/Interface/Texture.hpp
    )

    add_library(arcade_ncurses SHARED ${SRCS_NCURSES} ${HEADERS_NCURSES})
    set_target_properties(arcade_ncurses PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
    SET_TARGET_PROPERTIES(arcade_ncurses PROPERTIES PREFIX "")
    add_library(arcade_sfml SHARED ${SRCS_SFML} ${HEADERS_SFML})
    set_target_properties(arcade_sfml PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
    SET_TARGET_PROPERTIES(arcade_sfml PROPERTIES PREFIX "")
    add_library(arcade_sdl2 SHARED ${SRCS_SDL2} ${HEADERS_SDL2})
    set_target_properties(arcade_sdl2 PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
    SET_TARGET_PROPERTIES(arcade_sdl2 PROPERTIES PREFIX "")
    add_executable(arcade ${SRCS} ${HEADERS})
    set_target_properties(arcade PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/")
    target_link_libraries(arcade dl)
