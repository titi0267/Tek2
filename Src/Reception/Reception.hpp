/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Reception
*/

#pragma once
#include "../Utils/Utils.hpp"

class Reception {
    public:
        Reception(int ac, char **av);
        ~Reception();

    protected:
    private:
        int _cookingTime;
        int _cooksPerKitchen;
        int _timeToReplace;
        Utils _tools;
};
