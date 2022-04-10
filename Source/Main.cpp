/*
** EPITECH PROJECT, 2022
** OOP
** File description:
** Main
*/

#include "define.hpp"
#include "Error/Error.hpp"
#include "DlLib.hpp"
#include "Interface/Core.hpp"
#include "Games/Menu/Menu.hpp"

int main(int ac, char **av)
{
    if (ac == 1) {
        std::cout << "You need to specify the graphic library to use" << std::endl;
        return (ERROR);
    }
    Menu menu;
    /*std::deque<char *> libNames;
    libNames.push_back(av[1]);
    libNames.push_back((char *)("./lib/arcade_sfml.so"));
    libNames.push_back((char *)("./lib/arcade_sdl2.so"));*/
    Error error("error");
    Core core;
    menu.readDir();
    menu.sortLibsGames();
    menu.chooseFirstLib(&core, av[1]);
    menu.init(&core, av[1]);

    error.checkArgs(ac, av);
    //core.getGame()->init(&core);
    core.gameLoop(&menu);
    return (SUCCESS);
}
