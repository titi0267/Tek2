/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** System
*/

#pragma once

#include <set>
#include <vector>
#include "Entity.hpp"
#include "Component.hpp"

namespace ecs {
    class World;

    const std::size_t STAGES_NB = 7;
    enum Stages {
        NETWORK_UPDATE,
        TIME_UPDATE,
        INPUT_UPDATE,
        UPDATE,
        RENDER_UPDATE,
        DRAW_WORLD,
        DRAW_HUD,
    };

    class ASystem {
        protected:
        std::set<Entity> _entities;
        Signature _signature;
        Stages _stage = UPDATE;

        public:
        void addEntity(Entity entity) { _entities.insert(entity); };
        void removeEntity(Entity entity) { _entities.erase(entity); };

        virtual void setSignature(ComponentManager &component) = 0;
        virtual void update(World &world) = 0;

        const Signature &getSignature() { return _signature; };
        Stages getStage() { return _stage; };
    };

    class SystemAlreadyExists {};
    class SystemDoNotExists {};

    class SystemManager {
        using SystemHash = std::size_t;

        std::unordered_map<SystemHash, std::unique_ptr<ASystem>> _systems;
        std::unordered_map<Stages, std::vector<SystemHash>> _stages;

        public:
        SystemManager()
        {
            for (std::size_t i = 0; i < STAGES_NB; i++)
                _stages[(Stages) i] = std::vector<SystemHash>();
        }

        template<class T>
        void registerSystem(ComponentManager &component)
        {
            std::unique_ptr<ASystem> system = std::make_unique<T>();
            SystemHash hash = typeid(T).hash_code();
            Stages stage = system->getStage();

            if (_systems.find(hash) != _systems.end())
                throw SystemAlreadyExists();
            system->setSignature(component);
            _systems[hash] = std::move(system);
            _stages[stage].push_back(hash);
        }

        template<class T>
        void unregisterSystem()
        {
            SystemHash hash = typeid(T).hash_code();

            if (_systems.find(hash) == _systems.end())
                throw SystemDoNotExists();
            _systems.erase(hash);
            for (auto &[stage, systems] : _stages) {
                auto index = std::find(systems.begin(), systems.end(), hash);
                if (index != systems.end())
                    systems.erase(index);
            }
        }

        template<class T>
        T &getSystem()
        {
            SystemHash hash = typeid(T).hash_code();

            if (_systems.find(hash) != _systems.end())
                throw SystemDoNotExists();
            return *_systems[hash].get();
        }

        void updateStage(World &world, Stages stage)
        {
            for (SystemHash hash : _stages[stage])
                _systems[hash]->update(world);
        }

        void updateEntitySignature(Entity entity, Signature &signature)
        {
            for (auto &pair : _systems) {
                const Signature &systemSig = pair.second->getSignature();

                if ((systemSig & signature) == systemSig)
                    pair.second->addEntity(entity);
                else
                    pair.second->removeEntity(entity);
            }
        }

        void removeEntity(Entity entity)
        {
            for (auto &pair : _systems)
                pair.second->removeEntity(entity);
        }
    };
}
