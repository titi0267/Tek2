/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-alexandre.frantz
** File description:
** Nibbler
*/

#ifndef NIBBLER_HPP_
#define NIBBLER_HPP_

#include "../../../arcade-interface-master/IGameModule.hpp"
#include "../../../arcade-interface-master/ICore.hpp"
#include <deque>

class Nibbler : public IGameModule {
    public:
        Nibbler();
        ~Nibbler();

        void init(ICore *coreHandle);
        void update();
        void draw();
        void setGum(int headDirection);
        bool checkSnakePosX(unsigned random);
        bool checkSnakePosY(unsigned random);
        bool checkSnakeHeadPosX(unsigned random, int whichHead);
        bool checkSnakeHeadPosY(unsigned random, int whichHead);

    protected:
        ICore *_core;
        std::deque<ICore::Sprite> _sprite;
        bool _gum;
        int _snakeSize;
        //std::deque<ICore::Vector2u> _snakePos;
};

#endif /* !NIBBLER_HPP_ */
