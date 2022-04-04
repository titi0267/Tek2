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

class Pacman : public IGameModule {
    public:
        Pacman();
        ~Pacman();
        void init(ICore *coreHandle);
        void update();
        void draw();
};

#endif /* !PACMAN_HPP_ */
