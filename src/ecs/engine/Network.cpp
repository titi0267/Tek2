/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** Network
*/

#include "ecs/engine/Network.hpp"
#include "ecs/components/ColorTexture.hpp"
#include "ecs/components/DrawableModel.hpp"
#include "ecs/components/Text3D.hpp"
#include "ecs/components/Hitbox.hpp"

// MirrorEntity should NEVER be registered !
const ecs::ComponentHash ecs::MIRROR_COMPONENTS[ecs::NB_MIRROR_COMPONENTS] = {
    typeid(Transform).hash_code(),
    typeid(ecs::Hitbox).hash_code(),
    typeid(ecs::TextureRef).hash_code(),
    typeid(ecs::ModelRef).hash_code(),
    typeid(ecs::FontRef).hash_code(),
    typeid(ecs::Tint).hash_code(),
};
