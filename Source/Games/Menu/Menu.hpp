/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-alexandre.frantz
** File description:
** Menu
*/

#pragma once
#include "../../Interface/Core.hpp"
#include "../../DlLib.hpp"
#include <deque>
#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>

class Menu {
    public:
        Menu();
        ~Menu();
        void init(Core *coreHandle, char *av);
        void draw();
        void update();
        void readDir();
        void sortLibsGames();
        bool chooseFirstLib(char *av);
        //void constructMap();

    protected:
        Core *_core;
        DlLib _dl;
        std::deque<ICore::Sprite> _sprite;
        std::vector<char>_map;
        std::deque<std::string> _files;
        std::deque<std::string> _libs;
        std::deque<std::string> _games;
};
