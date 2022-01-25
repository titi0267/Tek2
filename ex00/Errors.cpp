/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD10pm-timothe.coniel
** File description:
** Errors
*/

#include "Errors.hpp"

NasaError::NasaError(std::string const &message, std::string const &component)
{
    _message = message;
    _component = component;
}

MissionCriticalError::MissionCriticalError(std::string const &message, std::string const &component) : NasaError(message, component)
{
}

LifeCriticalError::LifeCriticalError(std::string const &message, std::string const &component) : NasaError(message, component)
{
}

UserError::UserError(std::string const &message, std::string const &component) : NasaError(message, component)
{
}

CommunicationError::CommunicationError(std::string const &message, std::string const &component) : NasaError(message, component)
{
}

std::string const &NasaError::getComponent() const
{
    return _component;
}