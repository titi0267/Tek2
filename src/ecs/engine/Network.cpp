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
#include "ecs/components/PlayAnimation.hpp"
#include "ecs/components/Skin.hpp"
#include "ecs/components/Grid.hpp"

// MirrorEntity should NEVER be registered !
const ecs::ComponentHash ecs::MIRROR_COMPONENTS[ecs::NB_MIRROR_COMPONENTS] = {
    typeid(Transform).hash_code(),
    typeid(ecs::Movement).hash_code(),
    typeid(ecs::Hitbox).hash_code(),
    typeid(ecs::PlayerAction).hash_code(),
    typeid(ecs::TextureRef).hash_code(),
    typeid(ecs::ModelRef).hash_code(),
    typeid(ecs::FontRef).hash_code(),
    typeid(ecs::Tint).hash_code(),
    typeid(ecs::DrawableCube).hash_code(),
    typeid(ecs::Text3D).hash_code(),
    typeid(ecs::PlayAnimation).hash_code(),
    typeid(ecs::Skin).hash_code(),
    typeid(ecs::Grid).hash_code(),
};

void ecs::createUpdateLocalEntityBuffer(Entity entity, World &world, std::stringbuf &buffer)
{
    const NetworkCommand cmd = NetworkCommand::UPDATE_ENTITY;
    ComponentManager &compMan = world.getComponentManager();
    std::uint32_t total = 0;
    ComponentType type;
    std::uint32_t componentSize;

    for (const ComponentHash hash : MIRROR_COMPONENTS) {
        type = compMan.getComponentTypeByHash(hash);
        if (world.getComponentManager().hasComponentById(type, entity))
            total++;
    }
    buffer.sputn((char*) &cmd, sizeof(NetworkCommand));
    buffer.sputn((char*) &entity, sizeof(Entity));
    buffer.sputn((char*) &total, sizeof(std::uint32_t));
    for (const ComponentHash hash : MIRROR_COMPONENTS) {
        type = compMan.getComponentTypeByHash(hash);
        if (world.getComponentManager().hasComponentById(type, entity)) {
            componentSize = world.getComponentManager().getComponentSize(type);
            buffer.sputn((char*) &type, sizeof(ComponentType));
            buffer.sputn((char*) &componentSize, sizeof(std::uint32_t));
            buffer.sputn((char*) world.getComponentManager().getComponentByType(type, entity), componentSize);
        }
    }
}

void ecs::createKillLocalEntityBuffer(Entity entity, std::stringbuf &buffer)
{
    const NetworkCommand cmd = NetworkCommand::KILL_ENTITY;

    buffer.sputn((char*) &cmd, sizeof(NetworkCommand));
    buffer.sputn((char*) &entity, sizeof(Entity));
}
