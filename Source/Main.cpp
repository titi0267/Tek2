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
    Error error;
    DlLib dl;
    Core core;

    error.checkArgs(ac, av);
    dl.open(av[1]);
    dl.close();
    return (SUCCESS);
}
