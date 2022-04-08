/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-alexandre.frantz
** File description:
** Pacman
*/

#ifndef PACMAN_HPP_
#define PACMAN_HPP_

#include "../../../arcade-interface-master/IGameModule.hpp"
#include "../../../arcade-interface-master/ICore.hpp"
#include <deque>
#include <iostream>
#include <fstream>
#include <vector>

class Pacman : public IGameModule {
    public:
        Pacman();
        ~Pacman();
        void init(ICore *coreHandle);
        void update();
        void draw();
        void constructMap();
        bool movePacman(int i);
        void moveGhost();
        void updatePosition();
        int chooseDirection(int pos);
        bool checkWallGhost(int i);

    protected:
        ICore *_core;
        std::deque<ICore::Sprite> _sprite;
        int _direction;
        int _ghost1Direction;
        int _ghost2Direction;
        int _ghost3Direction;
        int _ghost4Direction;
        enum class Direction {
            up = 0,
            down = 1,
            right = 2,
            left = 3,
        };
        std::vector<char> _map;
        int _frameRate;
        int _ghostFrameRate;
        int _pacmanHead;
        int _pacGumEat;
        int _score;
        int _ghostOut;
        int _timer;
        std::vector<std::string> _ghostInHouse;
};

#endif /* !PACMAN_HPP_ */
