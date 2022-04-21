/*
** EPITECH PROJECT, 2022
** ftp
** File description:
** main
*/

#include "../include/prototype.h"
#include "../include/main_struct.h"

int main(int ac, char **av)
{
    if (parse_args(ac, av) == ERROR_CODE)
        return (ERROR_CODE);
    //socket_run(av);
}