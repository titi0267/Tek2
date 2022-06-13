/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** Network
*/

#include "ecs/engine/Network.hpp"
#include "ecs/components/ColorTexture.hpp"
#include "ecs/components/DrawableCube.hpp"
#include "ecs/components/DrawableModel.hpp"
#include "ecs/components/Text3D.hpp"
#include "ecs/components/Hitbox.hpp"
#include "ecs/components/PlayerInputs.hpp"
#include "ecs/components/Movement.hpp"

// MirrorEntity should NEVER be registered !
const ecs::ComponentHash ecs::MIRROR_COMPONENTS[ecs::NB_MIRROR_COMPONENTS] = {
    typeid(Transform).hash_code(),
    typeid(Movement).hash_code(),
    typeid(Hitbox).hash_code(),
    typeid(PlayerAction).hash_code(),
    typeid(TextureRef).hash_code(),
    typeid(ModelRef).hash_code(),
    typeid(FontRef).hash_code(),
    typeid(Tint).hash_code(),
    typeid(DrawableCube).hash_code(),
    typeid(Text3D).hash_code(),
};
