/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** World
*/

#pragma once

#include <memory>
#include "EntityManager.hpp"
#include "Component.hpp"
#include "System.hpp"
#include "Ressources.hpp"

namespace ecs {
    class EntityCommands;

    class World {
        EntityManager _entities;
        ComponentManager _components;
        SystemManager _systems;
        RessourcesManager _ressources;
        std::deque<Entity> _livingEntities;

        public:
        World() = default;
        ~World() = default;

        EntityManager &getEntityManager() { return _entities; };
        ComponentManager &getComponentManager() { return _components; };
        SystemManager &getSystemManager() { return _systems; };
        RessourcesManager &getRessourceManager() { return _ressources; };

        void updateClient();
        void updateServer();
        void killAllEntities();

        void decodeEntities(std::ifstream &file);
        void encodeEntity(Entity entity, std::ofstream &file);

        EntityCommands spawn();
        EntityCommands getEntityCommands(Entity entity);

        template<typename T>
        T &getComponent(Entity entity)
        {
            return _components.getComponent<T>(entity);
        }

        template<typename T>
        bool hasComponent(Entity entity)
        {
            return _components.hasComponent<T>(entity);
        }

        template<typename T>
        T &getRessource()
        {
            return _ressources.getRessource<T>();
        }

        template<typename T>
        void registerComponent()
        {
            _components.registerComponent<T>();
        }

        template<typename ...Ts>
        void registerComponents()
        {
            (_components.registerComponent<Ts>(), ...);
        }

        template<typename T>
        std::vector<Entity> query()
        {
            return _components.query<T>();
        }

        template<typename T>
        void registerSystem()
        {
            _systems.registerSystem<T>(_components);
        }

        template<typename ...Ts>
        void registerSystems()
        {
            (_systems.registerSystem<Ts>(_components), ...);
        }

        template<typename T>
        void unregisterSystem()
        {
            _systems.unregisterSystem<T>();
        }

        template<typename ...Ts>
        void unregisterSystems()
        {
            (_systems.unregisterSystem<Ts>(), ...);
        }

        template<typename T, typename ...Args>
        void insertRessource(Args... args)
        {
            _ressources.insertRessource<T>(args...);
        }

        std::deque<Entity> &getLivingEntities()
        {
            return _livingEntities;
        }
    };
}
