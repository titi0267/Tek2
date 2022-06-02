/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** Ressources
*/

#pragma once

#include <memory>
#include <unordered_map>

namespace ecs {
    class RessourceAlreadyExists {};
    class UnknownRessource {};

    class RessourcesManager {
        using RessourceHash = std::size_t;

        std::unordered_map<RessourceHash, std::shared_ptr<void>> _ressources;

        public:
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
