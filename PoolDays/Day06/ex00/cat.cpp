/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD06-timothe.coniel
** File description:
** cat
*/

#include <iostream>
#include <fstream>

void open_files(int ac, char **av)
{
    for (int i = 1; i < ac; i++) {
        std::ifstream file (av[i], std::ios::in);
        if (!file)
            std::cerr << "my_cat: " << av[i] << ": No such file or directory" << std::endl;
        else {
            std::cout << file.rdbuf();
            file.close();
        }
    }
}

int main(int ac, char **av)
{
    if (ac <= 1)
        std::cerr << "my_cat: Usage: ./my_cat file [...]"  << std::endl;
    else
        open_files(ac, av);
}