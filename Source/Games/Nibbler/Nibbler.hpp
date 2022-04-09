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
        int getDirection(int i) const;
        void setDirection(int direction, int i);
        void constructSnake();
        void constructMap();
        void updateSnakePos();
        void setNextDirection(int direction, int i);
        void rightCorner(int i);
        void headMoves();
        void bodyMoves(int i);
        void chooseCorner(int i);
        void upCorner(int i);
        void leftCorner(int i);
        void downCorner(int i);

    protected:
        struct Snake {
            ICore::Sprite _sprt;
            ICore::Sprite _nextSprt;
            int _direction;
            int _nextDirection;
            int isCorner;
        };
        ICore *_core;
        std::deque<Snake> _sprite;
        bool _gum;
        int _frameNext;
        int _snakeSize;
        std::deque<Snake> _snake;
        bool _addNewBody; //if true do not move last & before last element of snake
        int _direction;
        int _counter;
        int _frameKey;
        enum class Direction {
            up = 0,
            down = 1,
            right = 2,
            left = 3,
            corner = 4,
        };
        std::vector<char> _map;
        int _frameRate;

        //std::deque<ICore::Vector2u> _snakePos;
};

#endif /* !NIBBLER_HPP_ */
