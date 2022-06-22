/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** EntityCommands
*/

#pragma once

#include <algorithm>
#include "Entity.hpp"
#include "Component.hpp"
#include "World.hpp"
#include "SceneManager.hpp"

namespace ecs {
    class EntityCommands {
        Entity _entity;
        World &_world;

        public:
        EntityCommands(Entity entity, World &world) : _entity(entity), _world(world) {};
        EntityCommands(const EntityCommands &other) : _entity(other._entity), _world(other._world) {};
        ~EntityCommands() = default;

        template<typename T>
        EntityCommands &insert(const T &component)
        {
            ComponentType type = _world.getComponentManager().getComponentType<T>();
            Signature &signature = _world.getEntityManager().getSignature(_entity);

            _world.getComponentManager().addComponentToEntity<T>(_entity, component);
            signature[type] = true;
            _world.getSystemManager().updateEntitySignature(_entity, signature);
            return *this;
        }

        template<typename ...Ts>
        EntityCommands &insert(const Ts  ... components)
        {
            (insert<Ts>(components), ...);
            return *this;
        }

        EntityCommands &insertByType(ComponentType type)
        {
            Signature &signature = _world.getEntityManager().getSignature(_entity);

            _world.getComponentManager().addComponentToEntityByType(type, _entity);
            signature[type] = true;
            _world.getSystemManager().updateEntitySignature(_entity, signature);
            return *this;
        }

        template<typename T>
        EntityCommands &remove()
        {
            ComponentType type = _world.getComponentManager().getComponentType<T>();

            _world.getComponentManager().removeComponentToEntity<T>(_entity);
            _world.getEntityManager().getSignature(_entity)[type] = false;
            _world.getSystemManager().removeEntity(_entity);
            return *this;
        }

        void despawn()
        {
            Signature &sign = _world.getEntityManager().getSignature(_entity);
            std::deque<Entity> &living = _world.getLivingEntities();

            _world.getRessource<ecs::SceneManager>().getScene().entityKilled(_entity, _world);
            for (ComponentType i = 0; i < MAX_COMPONENTS; i++) {
                if (sign.test(i))
                    _world.getComponentManager().getIComponentArray(i)->removeEntity(_entity);
            }
            sign.reset();
            _world.getSystemManager().updateEntitySignature(_entity, sign);
            _world.getEntityManager().destroyEntity(_entity);
            living.erase(std::find(living.begin(), living.end(), _entity));
        }

        Entity getEntity() { return _entity; };
    };
}
