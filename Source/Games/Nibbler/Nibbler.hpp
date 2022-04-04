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

class Nibbler : public IGameModule {
    public:
        Nibbler();
        ~Nibbler();

        void init(ICore *coreHandle);
        void update();
        void draw();
};

#endif /* !NIBBLER_HPP_ */
