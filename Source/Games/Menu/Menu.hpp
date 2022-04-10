/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-alexandre.frantz
** File description:
** Menu
*/

#pragma once
#include "../../Interface/Core.hpp"
#include "../../DlLib.hpp"
#include "../../Error/Error.hpp"
#include <deque>
#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <string>

extern "C" {
    #include <string.h>
    #include <dlfcn.h>
}

class Core;
class Menu {
    public:
        Menu();
        ~Menu();
        void init(Core *coreHandle, char *av);
        void draw();
        void update();
        void readDir();
        void sortLibsGames();
        void manageSelected();
        void chooseFirstLib(Core *coreHandle, const char *av);
        //void constructMap();
        enum class Selected {
            Graphical, Games, Score
        };

    protected:
        Menu::Selected _selected;
        Core *_core;
        DlLib _dl;
        std::deque<ICore::Sprite> _sprite;
        std::vector<char>_map;
        std::deque<std::string> _files;
        std::deque<std::string> _libs;
        std::deque<std::string> _games;
        int _pixelPerCell;
        std::unique_ptr<IDisplayModule> (*_lib)(void);
        std::unique_ptr<IGameModule> (*_game)(void);
        void *_openLib;
        void *_openGame;
};
