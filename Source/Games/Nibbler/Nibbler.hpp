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
#include <iostream>
#include <fstream>
#include <vector>

class Nibbler : public IGameModule {
    public:
        Nibbler();
        ~Nibbler();

        void init(ICore *coreHandle);
        void update();
        void draw();
        void setGum();
        bool checkSnakePosX(unsigned random);
        bool checkSnakePosY(unsigned random);
        bool checkSnakeHeadPosX(unsigned random);
        bool checkSnakeHeadPosY(unsigned random);
        void gumEated();
        int getDirection() const;
        void setDirection(int direction);
        void constructSnake();
        void constructMap();

    protected:
        ICore *_core;
        std::deque<ICore::Sprite> _sprite;
        bool _gum;
        int _snakeSize;
        std::deque<ICore::Sprite> _snake;
        bool _addNewBody; //if true do not move last & before last element of snake
        int _direction;
        enum class Direction {
            up = 0,
            down = 1,
            right = 2,
            left = 3,
        };
        std::vector<char> _map;

        //std::deque<ICore::Vector2u> _snakePos;
};

#endif /* !NIBBLER_HPP_ */
