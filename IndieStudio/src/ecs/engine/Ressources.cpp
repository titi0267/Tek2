/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** Ressources
*/

#include "ecs/engine/Ressources.hpp"
#include "raylib/Window.hpp"

ecs::RessourcesManager::~RessourcesManager()
{
    RessourceHash windowHash = typeid(raylib::Window).hash_code();

    for (auto it = _ressources.rbegin(); it != _ressources.rend(); it++) {
        if (it->first != windowHash)
            _ressources.erase(it->first);
    }

    if (_ressources.find(windowHash) != _ressources.end())
        _ressources.erase(windowHash);
}
