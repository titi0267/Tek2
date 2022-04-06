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
        return (84);
    }
    std::deque<char *> libNames;
    libNames.push_back(av[1]);
    libNames.push_back("./lib/arcade_sfml.so");
    libNames.push_back("./lib/arcade_sdl2.so");
    Error error;
    DlLib dl(av[1]);
    Core core(libNames, 0);

    core.loadLibs(dl.getLib()); //lib to print
    core.loadGames(dl.getGame());
    std::cout << "ERREUR" << std::endl;
    error.checkArgs(ac, av);
    dl.close();
    return (SUCCESS);
}
