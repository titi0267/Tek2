/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD07am-timothe.coniel
** File description:
** WarpSystem
*/

#include "WarpSystem.hpp"

WarpSystem::QuantumReactor::QuantumReactor()
{
    _stability = true;
}

WarpSystem::Core::Core(WarpSystem::QuantumReactor *QuantumReactor_ptr)
{
    _coreReactor = QuantumReactor_ptr;
}

WarpSystem::Core::~Core()
{
    ;
}

WarpSystem::QuantumReactor *WarpSystem::Core::checkReactor()
{
    return (_coreReactor);
}

WarpSystem::QuantumReactor::~QuantumReactor()
{
    ;
}

bool WarpSystem::QuantumReactor::isStable()
{
    return (_stability);
}

void WarpSystem::QuantumReactor::setStability(bool stability)
{
    _stability = stability;
}
