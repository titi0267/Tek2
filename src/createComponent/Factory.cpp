/*
** EPITECH PROJECT, 2022
** $
** File description:
** Factory
*/

#include "../include/Factory.hpp"
#include "../include/Components.hpp"
#include "../Chipsets.hpp"

nts::Factory::Factory() : _components()
{
    _tick = 0;
}

void nts::Factory::setTick(size_t tick)
{
    _tick = tick;
}

void nts::Factory::addQueue(std::string cmd)
{
    _queue.push_back(cmd);
}

void nts::Factory::setupQueue()
{
    int queueLen = 0;

    for (auto &itr: _queue) {
        setInputValue(itr);
        queueLen++;
    }
    for (int i = 0; i != queueLen; i++)
        _queue.pop_back();
}

size_t nts::Factory::getTick() const
{
    return _tick;
}

std::unique_ptr<nts::IComponent> nts::Factory::createComponent(const std::string &compType)//, const std::string &name)
{
    if (compType == "input") {
        return std::make_unique<nts::Input>(); //compName provided by ludo
    } else if (compType == "output") {
        return std::make_unique<nts::Output>();
    } else if (compType == "false") {
        return std::make_unique<nts::False>();
    } else if (compType == "true") {
        return std::make_unique<nts::True>();
    } else if (compType == "clock") {
        return std::make_unique<nts::Clock>();
    } else if (compType == "4069") {
        return std::make_unique<nts::Comp4069>();
    } else if (compType == "4081") {
        return std::make_unique<nts::Comp4081>();
    } else if (compType == "4071") {
        return std::make_unique<nts::Comp4071>();
    }
}

void nts::Factory::storeComp(Chipsets comp)
{
    for (auto itr_input : comp.getInputs()) {
        _components.emplace((std::get<1>(itr_input)), createComponent(std::get<0>(itr_input)));
    }
    for (auto itr_output : comp.getOutputs()) {
        _components.emplace((std::get<1>(itr_output)), createComponent(std::get<0>(itr_output)));
    }
    for (auto itr_false : comp.getFalses()) {
        _components.emplace((std::get<1>(itr_false)), createComponent(std::get<0>(itr_false)));
    }
    for (auto itr_true : comp.getTrues()) {
        _components.emplace((std::get<1>(itr_true)), createComponent(std::get<0>(itr_true)));
    }
    for (auto itr_clock : comp.getClocks()) {
        _components.emplace((std::get<1>(itr_clock)), createComponent(std::get<0>(itr_clock)));
    }
    for (auto itr_comp : comp.getLogicComponents()) {
        _components.emplace((std::get<1>(itr_comp)), createComponent(std::get<0>(itr_comp)));
    }
    for (auto itr2 : comp.getChipsetLinks()) {
        _components.find(std::get<0>(itr2))->second->setLink
        (std::stoi(std::get<1>(itr2)), *(_components.find(std::get<2>(itr2))->second), std::stoi(std::get<3>(itr2)));
        _components.find(std::get<2>(itr2))->second->setLink
        (std::stoi(std::get<3>(itr2)), *(_components.find(std::get<0>(itr2))->second), std::stoi(std::get<1>(itr2)));
    }
}

std::map<std::string, std::unique_ptr<nts::IComponent >>& nts::Factory::getComp()
{
    return _components;
}

void nts::Factory::setInputValue(std::string str)
{
    Utils tools;
    std::vector<std::string> splitedValue = tools.split(str, '=');
    auto itr = std::begin(_components);
    nts::Tristate toSet = nts::UNDEFINED;

    if (splitedValue[1] == "U")
        toSet = nts::UNDEFINED;
    else if (splitedValue[1] == "0")
        toSet = nts::FALSE;
    else
        toSet = nts::TRUE;

    for (; itr != _components.end(); itr++) {
        if (itr->second->getType() == "input" && itr->first == splitedValue[0]) {
            itr->second->setState(1, toSet);
            break;
        }
        if (itr->second->getType() == "clock" && itr->first == splitedValue[0]) {
            itr->second->setState(1, nts::Gates::Not(toSet));
            break;
        }
    }
}

nts::Factory::~Factory()
{
}
