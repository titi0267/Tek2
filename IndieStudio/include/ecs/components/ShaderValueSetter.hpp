/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** ShaderValueSetter
*/

#pragma once

#include "ecs/engine/World.hpp"

namespace ecs {
    using ShaderValueSetterFct = void (*)(ecs::World &world, ecs::Entity entity);

    struct ShaderValueSetter {
        ShaderValueSetterFct fct;

        ShaderValueSetter(ShaderValueSetterFct fct = nullptr) : fct(fct) {};
    };
};
