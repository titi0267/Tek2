/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** IComponent
*/

#include <unistd.h>
#include <vector>
#include <map>
#include <iostream>

namespace nts
{
    enum Tristate {
        UNDEFINED = (-true),
        TRUE = true,
        FALSE = false
        };

    class IComponent
    {
        public :
        virtual ~IComponent() = default;
        virtual void simulate(size_t tick) = 0;
        virtual nts::Tristate compute(size_t pin) = 0;
        virtual void setLink(size_t pin, nts::IComponent &other,size_t otherPin ) = 0;
        virtual void dump() const = 0;
    };
}