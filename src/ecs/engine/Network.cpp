/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** Network
*/

#include "ecs/engine/Network.hpp"
#include "ecs/components/ColorTexture.hpp"

const ecs::ComponentHash ecs::MIRROR_COMPONENTS[ecs::NB_MIRROR_COMPONENTS] = {
    typeid(Transform).hash_code(),
    typeid(Tint).hash_code(),
};
