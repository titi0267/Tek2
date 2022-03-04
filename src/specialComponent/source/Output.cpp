/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** Output
*/

#include "../include/Output.hpp"

nts::Output::Output(int compNumber, const std::string &name)
{
    std::cout << "test";
    setComp(name, "output");
    _pins.push_back(nts::Tristate::UNDEFINED);
    std::cout << _pins[0];
}

nts::Tristate nts::Output::compute(size_t pin)
{
    return getState()[0];
}

void nts::Output::setLink(size_t pin, nts::IComponent &other, size_t otherPin)
{
    _saveLink.emplace(pin, Link{other, otherPin});
}

void nts::Output::simulate(size_t tick)
{
    setTick(tick);
    auto itr = _saveLink.begin();
    setState(itr->first, itr->second.component.compute(itr->second.pin));
}

void nts::Output::dump() const
{
    //std::cout << "Output(s):" << std::endl << "  " << getName() << ": " << _pin.getPin(0) << std::endl;
}

nts::Output::~Output()
{
}
