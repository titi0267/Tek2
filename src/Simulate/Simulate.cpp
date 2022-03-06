/*
** EPITECH PROJECT, 2022
** Visual Studio Live Share (Workspace)
** File description:
** Simulate
*/

#include "Simulate.hpp"

nts::Tristate secondPartRec(nts::IComponent &comp)
{
    if (comp.getType() == "input")
        return comp.getState()[0];
}

void nts::Simulate::simulateLoop(nts::Factory &factory)
{
    factory.setupQueue();
    factory.setTick(factory.getTick() + 1);
    for (auto &itr : factory.getComp()) {
        if ((itr.second->getType() == "output"))
            itr.second->compute(1);
    }
}