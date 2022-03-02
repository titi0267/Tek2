/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** Components
*/

#include "../include/Components.hpp"
#include "../specialComponent/include/Input.hpp"
#include "../specialComponent/include/Output.hpp"

nts::Components::Components() : _compNumber(0)
{
}

void nts::Components::setComp(int compNumber, std::string compName)
{
    _saveComp.insert(std::pair<std::string, int>(compName, compNumber));
}

std::map<std::string, int>::const_iterator nts::Components::getComp(std::string compName) const
{
    std::map<std::string, int>::const_iterator itr;

    itr = _saveComp.find(compName);
    return itr;
}

void nts::Components::newComp()
{
    _compNumber += 1;
}

int nts::Components::getCompNum() const
{
    return _compNumber;
}

std::unique_ptr<nts::Components> nts::Components::createComponent(const std::string &compType)
{
    if (compType == "Input") {
        nts::Components::newComp();
        return std::make_unique<nts::Input>(getCompNum(), "compName"); //compName provided by ludo
    }
    else if (compType == "Output") {
        return std::make_unique<nts::Output>(getCompNum(), "compName");
    }
}

nts::Components::~Components()
{
}
