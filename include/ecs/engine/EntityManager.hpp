/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** EntityManager
*/

#pragma once

#include <cstdint>
#include <deque>
#include <map>
#include <bitset>

#include "Entity.hpp"
#include "Component.hpp"

namespace ecs {
    class NoEntityAvailable {};

    class EntityManager {
        std::deque<Entity> _availableEntities;
        std::array<Signature, MAX_ENTITIES> _signatures;

        public:
        EntityManager()
        {
            _availableEntities.resize(MAX_ENTITIES);
            for (std::size_t i = 0; i < MAX_ENTITIES; i++)
                _availableEntities[i] = ((Entity) i);
        };

        Entity createEntity()
        {
            Entity entity;

            if (_availableEntities.empty())
                throw NoEntityAvailable();
            entity = _availableEntities.front();
            _availableEntities.pop_front();
            return entity;
        }

        void destroyEntity(Entity entity)
        {
            _availableEntities.push_back(entity);
            _signatures[(size_t) entity].reset();
        }

        void setSignature(Entity entity, Signature &signature)
        {
            _signatures[(size_t) entity] = signature;
        }

        Signature &getSignature(Entity entity)
        {
            return _signatures[(size_t) entity];
        }

        void reset()
        {
            _availableEntities.clear();
            _availableEntities.resize(MAX_ENTITIES);
            for (std::size_t i = 0; i < MAX_ENTITIES; i++) {
                _availableEntities[i] = ((Entity) i);
                _signatures[i] = {};
            }
        }
    };
}
