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

int main(int ac, char **av)
{
    if (ac == 1) {
        std::cout << "You need to specify the graphic library to use" << std::endl;
        return (ERROR);
    }
    std::deque<char *> libNames;
    libNames.push_back(av[1]);
    libNames.push_back((char *)("./lib/arcade_sfml.so"));
    libNames.push_back((char *)("./lib/arcade_sdl2.so"));
    Error error;
    Core core(libNames, 0);

    error.checkArgs(ac, av);
    core.getGame()->init(&core);
    core.gameLoop();
    return (SUCCESS);
}
