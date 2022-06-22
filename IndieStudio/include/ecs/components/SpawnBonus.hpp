/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** SpawnBonus
*/

#pragma once

#include "ecs/engine/World.hpp"
#include "ecs/engine/Component.hpp"
#include "ecs/components/Player.hpp"

namespace ecs {
    enum Bonus {
        BONUS_BOMB,
        BONUS_BOOTS,
        BONUS_RANGE,
        BONUS_TIG,
        BONUS_COUNT,
    };

    using BonusApplyEffectFct = void (*)(ecs::Player &player);

    extern const std::unordered_map<Bonus, BonusApplyEffectFct> BONUS_FCT;

    struct SpawnBonus {
        Bonus bonus = BONUS_COUNT;

        SpawnBonus(Bonus bonus = BONUS_COUNT) : bonus(bonus) {};
    };

    class SpawnBonusUpdateSystem : public ecs::ASystem {
        public:
        SpawnBonusUpdateSystem() { _stage = ecs::Stages::UPDATE; };

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };
}
