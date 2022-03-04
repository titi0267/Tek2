/*
** EPITECH PROJECT, 2022
** $
** File description:
** Factory
*/

#include "../include/Factory.hpp"
#include "../include/Components.hpp"
#include "../specialComponent/include/Input.hpp"
#include "../specialComponent/include/Output.hpp"
#include "../Chipsets.hpp"

nts::Factory::Factory()
{
}

void nts::Factory::newComp()
{
    _compNumber += 1;
}

int nts::Factory::getCompNum() const
{
    return _compNumber;
}

std::unique_ptr<nts::Components> nts::Factory::createComponent(const std::string &compType, const std::string &name)
{
    if (compType == "input") {
        nts::Factory::newComp();
        return std::make_unique<nts::Input>(getCompNum(), name); //compName provided by ludo
    }
    //else if (compType == "output") {
        return std::make_unique<nts::Output>(getCompNum(), name);
    //}
}

int nts::Factory::getComponentByName(std::string name)
{
    auto itr = _components.begin();
    int index = 0;

    for (; itr != _components.end(); ++itr, index++) {
        if ((*itr).getComp() == name)
            return (index);
    }
    return (-1);
}

void nts::Factory::storeComp(Chipsets comp)
{
    for (auto itr : comp.getInputs()) {
        _components.push_back(*createComponent("input", std::get<1>(itr)).get());
    }
    for (auto itr1 : comp.getOutputs()) {
        _components.push_back(*createComponent("output", std::get<1>(itr1)).get());
    }
    for (auto itr2 : comp.getChipsetLinks()) {
        _components[getComponentByName(std::get<0>(itr2))].setLink
        (std::stoi(std::get<1>(itr2)), _components[getComponentByName(std::get<2>(itr2))], std::stoi(std::get<3>(itr2)));
    }
}

std::vector<nts::Components> nts::Factory::getComp() const
{
    return _components;
}

void nts::Factory::setInputValue(std::string str)
{
    Utils tools;
    std::vector<std::string> splitedValue = tools.split(str, '=');
    auto itr = std::begin(_components);
    nts::Tristate toSet = nts::UNDEFINED;
    bool hasBeenSet = false;

    if (splitedValue[1] == "U")
        toSet = nts::UNDEFINED;
    else if (splitedValue[1] == "0")
        toSet = nts::FALSE;
    else
        toSet = nts::TRUE;

    for (auto itr : _components) {
        if ((itr).getType() == "input" && (itr).getComp() == splitedValue[0]) {
            (itr).setState(1, toSet);
            hasBeenSet = true;
            break;
        }
    }
    if (!hasBeenSet)
        std::cout << "This input doesn't exist\n";
}

nts::Factory::~Factory()
{
}
