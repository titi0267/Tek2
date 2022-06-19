/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** Ressources
*/

#pragma once

#include <memory>
#include <map>
#include "raylib/Window.hpp"

namespace ecs {
    class RessourceAlreadyExists {};
    class UnknownRessource {};

    class RessourcesManager {
        using RessourceHash = std::size_t;

        std::map<RessourceHash, std::shared_ptr<void>> _ressources;

        public:
        ~RessourcesManager()
        {
            RessourceHash windowHash = typeid(raylib::Window).hash_code();

            for (auto it = _ressources.rbegin(); it != _ressources.rend(); it++) {
                if (it->first != windowHash)
                    _ressources.erase(it->first);
            }
            if (_ressources.find(windowHash) != _ressources.end())
                _ressources.erase(windowHash);
        }

        template<typename T, typename ...Args>
        void insertRessource(Args ...args)
        {
            RessourceHash hash = typeid(T).hash_code();

            if (_ressources.find(hash) != _ressources.end())
                throw RessourceAlreadyExists();
            _ressources[hash] = std::make_shared<T>(args...);
        }

        template<typename T>
        void removeRessource()
        {
            RessourceHash hash = typeid(T).hash_code();

            if (_ressources.find(hash) == _ressources.end())
                throw UnknownRessource();
            _ressources.erase(hash);
        }

        template<typename T>
        T &getRessource()
        {
            RessourceHash hash = typeid(T).hash_code();

            if (_ressources.find(hash) == _ressources.end())
                throw UnknownRessource();
            return *((T*) _ressources[hash].get());
        }
    };
}
