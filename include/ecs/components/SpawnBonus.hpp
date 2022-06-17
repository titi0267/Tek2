/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** SpawnBonus
*/

#pragma once
#include "ecs/engine/World.hpp"
#include "ecs/engine/Component.hpp"

namespace ecs {
    enum Bonus {
        BOMBBONUS,
        BOOTS,
        EXPLODE,
        TIG,
        NOTHING
    };
    struct SpawnBonus {
        Bonus _bonusType = NOTHING;

        SpawnBonus() {};
        Bonus getBonus() const { return _bonusType; };
    };
    class SpawnBonusUpdateSystem : public ecs::ASystem {
        public:
        SpawnBonusUpdateSystem() { _stage = ecs::Stages::UPDATE; };

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };
}