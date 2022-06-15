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
    typeid(PlayAnimation).hash_code(),
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
