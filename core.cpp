/*
** EPITECH PROJECT, 2022
** core.cpp for Rush3 Epitech 2025
** File description:
** core
*/

#include "core.hpp"

int main(int ac, char **av, char **env)
{
    if (ac == 1) {
        Window b;
        b.printWindow();
    } else {
        ncursesMain();
    }

    Get_file a;
    struct utsname unameData;
    uname(&unameData);
    std::cout <<  a.getTime() << std::endl;
    std::cout << a.getHostname() << std::endl;
    std::cout << a.getUsername() << std::endl;
    std::cout << a.getOsName() << std::endl;
    std::cout << a.getModel() << std::endl;
    //std::cout << a.getCores() << std::endl;
    //std::cout << a.getActivity() << std::endl;
}
