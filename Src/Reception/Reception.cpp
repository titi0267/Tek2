/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Reception
*/

#include "Reception.hpp"
#include "../Error/Error.hpp"

Reception::Reception(int ac, char **av)
{
    if (ac != 4)
        throw (Error("Not Enough Arguments"));
    for (int i = 1; av[i]; i++) {
        if (!_tools.is_number(av[i]))
            throw (Error("Argument is not a number"));
    }
    _cookingTime = std::atoi(av[1]);
    _cooksPerKitchen = std::atoi(av[2]);
    _timeToReplace = std::atoi(av[3]);
}

void Reception::loop()
{
    std::string buff = "";

    while (1) {
        std::cout << "Waiter : What would you like to order ?" << std::endl;
        std::cin >> buff;
        if (!buff.compare("No"))
            break;
    }
}

Reception::~Reception()
{
}
