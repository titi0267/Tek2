cmake_minimum_required(VERSION 3.17)

project(arcade)

set(SRCS
    Source/Main.cpp
    Source/Error/Error.cpp
    Source/DlLib.cpp
    Source/Interface/Core.cpp
    Source/Interface/Texture.cpp
    Source/Games/Menu/Menu.cpp
    )

set(HEADERS
    arcade-interface-master/ICore.hpp
    arcade-interface-master/IDisplayModule.hpp
    arcade-interface-master/IGameModule.hpp
    Source/Error/Error.hpp
    Source/define.hpp
    Source/DlLib.hpp
    Source/Interface/Core.hpp
    Source/Interface/Texture.hpp
    Source/Games/Menu/Menu.hpp
    )

set(SRCS_PACMAN
    Source/Games/Pacman/Pacman.cpp
)

set(HEADERS_PACMAN
    arcade-interface-master/ICore.hpp
    arcade-interface-master/IGameModule.hpp
    Source/Games/Pacman/Pacman.hpp
)

set(SRCS_NIBBLER
    Source/Games/Nibbler/Nibbler.cpp
)

set(HEADERS_NIBBLER
    arcade-interface-master/ICore.hpp
    arcade-interface-master/IGameModule.hpp
    Source/Games/Nibbler/Nibbler.hpp
)

set(SRCS_NCURSES
    Source/Graphical/nCurses/Ncurses.cpp
    Source/Error/Error.cpp
    Source/Interface/RawTexture.cpp
)

set(HEADERS_NCURSES
    arcade-interface-master/ICore.hpp
    arcade-interface-master/IDisplayModule.hpp
    Source/Error/Error.hpp
    Source/Graphical/nCurses/Ncurses.hpp
    Source/Interface/RawTexture.hpp
    Source/define.hpp
)

set(HEADERS_SFML
    arcade-interface-master/ICore.hpp
    arcade-interface-master/IDisplayModule.hpp
    arcade-interface-master/IGameModule.hpp
    Source/Error/Error.hpp
    Source/Graphical/SFML/Sfml.hpp
    Source/Interface/RawTexture.hpp
    Source/define.hpp
)

set(HEADERS_SDL2
    arcade-interface-master/ICore.hpp
    arcade-interface-master/IDisplayModule.hpp
    arcade-interface-master/IGameModule.hpp
    Source/Error/Error.hpp
    Source/Graphical/Sdl2/Sdl2.hpp
    Source/Interface/RawTexture.hpp
    Source/define.hpp
)

set(SRCS_SDL2
    Source/Graphical/Sdl2/Sdl2.cpp
    Source/Interface/RawTexture.cpp
    Source/Error/Error.cpp
)

set(SRCS_SFML
    Source/Graphical/SFML/Sfml.cpp
    Source/Interface/RawTexture.cpp
    Source/Error/Error.cpp
)

    add_library(arcade_ncurses SHARED ${SRCS_NCURSES} ${HEADERS_NCURSES})
    set_target_properties(arcade_ncurses PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
    SET_TARGET_PROPERTIES(arcade_ncurses PROPERTIES PREFIX "")
    target_link_libraries(arcade_ncurses ncurses)
    add_library(arcade_sfml SHARED ${SRCS_SFML} ${HEADERS_SFML})
    set_target_properties(arcade_sfml PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
    SET_TARGET_PROPERTIES(arcade_sfml PROPERTIES PREFIX "")
    target_link_libraries(arcade_sfml sfml-window sfml-system sfml-graphics)
    add_library(arcade_sdl2 SHARED ${SRCS_SDL2} ${HEADERS_SDL2})
    set_target_properties(arcade_sdl2 PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
    SET_TARGET_PROPERTIES(arcade_sdl2 PROPERTIES PREFIX "")
    target_link_libraries(arcade_sdl2 SDL2 SDL2_image SDL2_ttf)
    add_library(arcade_pacman SHARED ${SRCS_PACMAN} ${HEADERS_PACMAN})
    set_target_properties(arcade_pacman PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
    SET_TARGET_PROPERTIES(arcade_pacman PROPERTIES PREFIX "")
    add_library(arcade_nibbler SHARED ${SRCS_NIBBLER} ${HEADERS_NIBBLER})
    set_target_properties(arcade_nibbler PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
    SET_TARGET_PROPERTIES(arcade_nibbler PROPERTIES PREFIX "")
    add_executable(arcade ${SRCS} ${HEADERS})
    set_target_properties(arcade PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/")
    target_link_libraries(arcade dl)
    target_compile_options(arcade PRIVATE -fno-gnu-unique)
