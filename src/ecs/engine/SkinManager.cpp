/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** SkinManager
*/

#include <algorithm>
#include <stdexcept>
#include <iostream>
#include "ecs/engine/SkinManager.hpp"

ecs::SkinManager::SkinManager() :
    _availaibleSkins({"ludovic", "mathieu", "jeffrey", "tom", "timothe", "kevin", "simon", "leo"})
{
}

const std::string &ecs::SkinManager::assignRandomSkin(PlayerId id)
{
    int index;

    if (_availaibleSkins.empty())
        throw std::runtime_error("No available skins");
    index = std::rand() % _availaibleSkins.size();
    _assignedSkins.insert({id, _availaibleSkins.at(index)});
    _availaibleSkins.erase(std::find(_availaibleSkins.begin(), _availaibleSkins.end(), _availaibleSkins.at(index)));
    return _assignedSkins.at(id);
}

const std::string &ecs::SkinManager::assignFirstSkin(PlayerId id)
{
    if (_availaibleSkins.empty())
        throw std::runtime_error("No available skins");
    _assignedSkins.insert({id, _availaibleSkins[0]});
    _availaibleSkins.erase(_availaibleSkins.begin());
    return _assignedSkins.at(id);
}

const std::string &ecs::SkinManager::assignLastSkin(PlayerId id)
{
    if (_availaibleSkins.empty())
        throw std::runtime_error("No available skins");
    _assignedSkins.insert({id, _availaibleSkins[_availaibleSkins.size() - 1]});
    _availaibleSkins.erase(_availaibleSkins.end() - 1);
    return _assignedSkins.at(id);
}

void ecs::SkinManager::assignSkinToPlayer(const std::string &skin, PlayerId id)
{
    auto it = std::find(_availaibleSkins.begin(), _availaibleSkins.end(), skin);

    if (it == _availaibleSkins.end())
        throw std::runtime_error("Skin doesn't exists or is already assigned");
    _assignedSkins.insert({id, skin});
    _availaibleSkins.erase(it);
}

void ecs::SkinManager::unassignedSkin(PlayerId id, bool front)
{
    if (_assignedSkins.find(id) == _assignedSkins.end())
        throw std::runtime_error("Player has no assigned skin");
    if (front)
        _availaibleSkins.push_front(_assignedSkins.at(id));
    else
        _availaibleSkins.push_back(_assignedSkins.at(id));
    _assignedSkins.erase(id);
}

const std::string &ecs::SkinManager::getPlayerSkin(PlayerId id)
{
    return _assignedSkins.at(id);
}

bool ecs::SkinManager::hasSkinAssigned(PlayerId id)
{
    return _assignedSkins.find(id) != _assignedSkins.end();
}
