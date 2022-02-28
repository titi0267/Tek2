/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** Error
*/

#pragma once

#include <string>

class Error : public std::exception
{
    public:
        Error(std::string);
        ~Error();
        const char *what();

    protected:
    private:
        std::string _message;
};
