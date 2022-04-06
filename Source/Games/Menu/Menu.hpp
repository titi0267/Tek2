/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-alexandre.frantz
** File description:
** Menu
*/

#pragma once
#include "../../../arcade-interface-master/IGameModule.hpp"
#include "../../../arcade-interface-master/ICore.hpp"
#include <deque>
#include <iostream>

class Menu : public IGameModule {
    public:
        Menu();
        ~Menu();
        void init(ICore *coreHandle);
        void draw();
        void update();

    protected:
        ICore *_core;
        std::deque<ICore::Sprite> _sprite;
};
