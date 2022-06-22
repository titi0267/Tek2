/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** Component
*/

#pragma once

#include <bitset>
#include <typeinfo>
#include <unordered_map>
#include <array>
#include <memory>
#include <vector>
#include <algorithm>

#include "Entity.hpp"

namespace ecs {
    using ComponentType = std::uint8_t;
    const ComponentType MAX_COMPONENTS = 64;

    using ComponentHash = std::size_t;

    using Signature = std::bitset<MAX_COMPONENTS>;

    class TooManyComponentRegistered {};
    class UnknownComponent {};
    class EnityDoNotHaveComponent {};

    class IComponentArray {
        public:
        virtual void addEntity(Entity entity) = 0;
        virtual void removeEntity(Entity entity) = 0;
        virtual void *getComponentPtr(Entity entity) = 0;
        virtual bool isEntityRegistered(Entity entity) = 0;
        virtual std::size_t getComponentSize() = 0;
        virtual void reset() = 0;
    };

    template<typename T>
    class ComponentArray : public IComponentArray {
        std::array<T, MAX_ENTITIES> _components;
        std::unordered_map<Entity, size_t> _entityToIndex;
        std::unordered_map<size_t, Entity> _indexToEntity;
        std::size_t _nextIndex = 0;

        public:
        void addEntity(Entity entity)
        {
            _entityToIndex[entity] = _nextIndex;
            _indexToEntity[_nextIndex] = entity;
            _nextIndex++;
        }

        void addEntity(Entity entity, const T &component)
        {
            _components[_nextIndex] = component;
            _entityToIndex[entity] = _nextIndex;
            _indexToEntity[_nextIndex] = entity;
            _nextIndex++;
        }

        void removeEntity(Entity entity)
        {
            size_t removeIndex;
            size_t lastIndex;
            Entity lastEntity;

            if (_entityToIndex.find(entity) == _entityToIndex.end())
                throw EnityDoNotHaveComponent();
            if (_nextIndex > 1) {
                removeIndex = _entityToIndex[entity];
                lastIndex = _nextIndex - 1;
                lastEntity = _indexToEntity[lastIndex];
                _components[removeIndex] = _components[lastIndex];
                _entityToIndex.erase(entity);
                _indexToEntity.erase(lastIndex);
                _entityToIndex[lastEntity] = removeIndex;
                _indexToEntity[removeIndex] = lastEntity;
            }
            _nextIndex--;
        }

        T &getComponent(Entity entity)
        {
            if (_entityToIndex.find(entity) == _entityToIndex.end())
                throw EnityDoNotHaveComponent();
            return _components[_entityToIndex[entity]];
        }

        void *getComponentPtr(Entity entity)
        {
            if (_entityToIndex.find(entity) == _entityToIndex.end())
                throw EnityDoNotHaveComponent();
            return &_components[_entityToIndex[entity]];
        }

        bool isEntityRegistered(Entity entity)
        {
            return _entityToIndex.find(entity) != _entityToIndex.end();
        }

        std::vector<Entity> getEntities()
        {
            std::vector<Entity> entities(_entityToIndex.size());

            std::transform(_entityToIndex.begin(), _entityToIndex.end(), entities.begin(), [](auto pair){return pair.first;});
            return entities;
        }

        std::size_t getComponentSize()
        {
            return sizeof(T);
        }

        void reset()
        {
            for (int i = 0; i < MAX_ENTITIES; i++)
                _components[i] = {};
            _entityToIndex.clear();
            _indexToEntity.clear();
            _nextIndex = 0;
        }
    };

    class ComponentManager {
        ComponentType _nextComponentType = 0;
        std::unordered_map<ComponentHash, ComponentType> _componentTypes;
        std::unordered_map<ComponentType, std::unique_ptr<IComponentArray>> _componentsArrays;

        template<typename T>
        ComponentArray<T> *getComponentArray(ComponentType type)
        {
            return (ComponentArray<T>*) (_componentsArrays[type].get());
        }

        public:
        ComponentManager()
        {
            _componentTypes.reserve(MAX_COMPONENTS);
        }

        template<typename T>
        void registerComponent()
        {
            ComponentHash hash = typeid(T).hash_code();

            if (_nextComponentType == MAX_COMPONENTS)
                throw TooManyComponentRegistered();
            _componentTypes[hash] = _nextComponentType;
            _componentsArrays[_nextComponentType] = std::make_unique<ComponentArray<T>>();
            _nextComponentType++;
        };

        template<typename T>
        ComponentType getComponentType()
        {
            ComponentHash hash = typeid(T).hash_code();

            return getComponentTypeByHash(hash);
        }

        ComponentType getComponentTypeByHash(ComponentHash hash)
        {
            if (_componentTypes.find(hash) == _componentTypes.end())
                throw UnknownComponent();
            return _componentTypes[hash];
        }

        template<typename ...Ts>
        Signature generateSignature()
        {
            Signature signature;

            (signature.set(getComponentType<Ts>(), true), ...);
            return (signature);
        }

        template<typename T>
        void addComponentToEntity(Entity entity, const T &component)
        {
            ComponentHash hash = typeid(T).hash_code();

            if (_componentTypes.find(hash) == _componentTypes.end())
                throw UnknownComponent();
            getComponentArray<T>(_componentTypes[hash])->addEntity(entity, component);
        }

        template<typename T>
        void removeComponentToEntity(Entity entity)
        {
            ComponentHash hash = typeid(T).hash_code();

            if (_componentTypes.find(hash) == _componentTypes.end())
                throw UnknownComponent();
            getComponentArray<T>(_componentTypes[hash])->removeEntity(entity);
        }

        template<typename T>
        T &getComponent(Entity entity)
        {
            ComponentHash hash = typeid(T).hash_code();

            if (_componentTypes.find(hash) == _componentTypes.end())
                throw UnknownComponent();
            return getComponentArray<T>(_componentTypes[hash])->getComponent(entity);
        }

        template<typename T>
        bool hasComponent(Entity entity)
        {
            ComponentHash hash = typeid(T).hash_code();

            if (_componentTypes.find(hash) == _componentTypes.end())
                throw UnknownComponent();
            return getComponentArray<T>(_componentTypes[hash])->isEntityRegistered(entity);
        }

        template<typename T>
        std::vector<Entity> query()
        {
            ComponentHash hash = typeid(T).hash_code();

            if (_componentTypes.find(hash) == _componentTypes.end())
                throw UnknownComponent();
            return getComponentArray<T>(_componentTypes[hash])->getEntities();
        }

        void addComponentToEntityByType(ComponentType type, Entity entity)
        {
            _componentsArrays[type]->addEntity(entity);
        }

        void *getComponentByType(ComponentType type, Entity entity)
        {
            return _componentsArrays[type]->getComponentPtr(entity);
        }

        bool hasComponentById(ComponentType type, Entity entity)
        {
            return _componentsArrays[type]->isEntityRegistered(entity);
        }

        std::size_t getComponentSize(ComponentType type)
        {
            return _componentsArrays[type]->getComponentSize();
        }

        IComponentArray *getIComponentArray(ComponentType type)
        {
            return _componentsArrays[type].get();
        }

        void reset()
        {
            for (auto &[type, comp] : _componentsArrays)
                comp->reset();
        }
    };
}
