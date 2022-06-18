/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** setup
*/

#include "Setup.hpp"

#include "ecs/engine/Network.hpp"

#include "ecs/components/DrawableCube.hpp"
#include "ecs/components/DrawableModel.hpp"
#include "ecs/components/Hitbox.hpp"
#include "ecs/components/Clickable.hpp"
#include "ecs/components/Hoverable.hpp"
#include "ecs/components/HoverTint.hpp"
#include "ecs/components/HoverRotate.hpp"
#include "ecs/components/Text3D.hpp"
#include "ecs/components/ColorTexture.hpp"
#include "ecs/components/SceneMoveElement.hpp"
#include "ecs/components/PlayerInputs.hpp"
#include "ecs/components/Movement.hpp"
#include "ecs/components/PlayAnimation.hpp"
#include "ecs/components/Skin.hpp"
#include "ecs/components/BackgroundRotation.hpp"
#include "ecs/components/Timer.hpp"
#include "ecs/components/FPSButton.hpp"
#include "ecs/components/FullscreenButton.hpp"
#include "ecs/components/KeyRecorder.hpp"
#include "ecs/components/ResolutionButton.hpp"
#include "ecs/components/TextInput.hpp"
#include "ecs/components/ToggleButton.hpp"
#include "ecs/components/Grid.hpp"
#include "ecs/components/CameraFollow.hpp"
#include "ecs/components/Intro.hpp"
#include "ecs/components/ItemRotation.hpp"
#include "ecs/components/Player.hpp"
#include "ecs/components/GridPosition.hpp"
#include "ecs/components/Bomb.hpp"
#include "ecs/components/Player.hpp"
#include "ecs/components/Water.hpp"
#include "ecs/components/DestructibleTile.hpp"
#include "ecs/components/SpawnBonus.hpp"
#include "ecs/components/Ai.hpp"
#include "ecs/components/Disappear.hpp"
#include "ecs/components/LaunchButton.hpp"
#include "ecs/components/Light.hpp"

// Those components are mirrored between clients and server
// THOSE COMPONENTS SHOULD ALWAYS BE REGISTERED FIRST !!
void bomberman::registerCriticalComponents(ecs::World &world)
{
    world.registerComponents<Transform, ecs::Movement, ecs::Hitbox, ecs::PlayerAction,
    ecs::TextureRef, ecs::ModelRef, ecs::FontRef, ecs::Tint, ecs::DrawableCube, ecs::Text3D,
    ecs::PlayAnimation, ecs::Skin, ecs::Grid, ecs::ItemRotation, ecs::Light>();
}

void bomberman::registerBothSide(ecs::World &world)
{
    world.registerComponent<ecs::Timer>();
    world.registerSystems<ecs::TimerUpdateSystem, ecs::ItemRotationUpdateSystem>();
}

void bomberman::registerServerSide(ecs::World &world)
{
    world.registerComponents<ecs::Player, ecs::GridPosition, ecs::Bomb,
    ecs::Water, ecs::DestructibleTile, ecs::SpawnBonus, ecs::Ai>();
    world.registerSystems<ecs::AnimationUpdateSystem>();
}

void bomberman::registerPhysics(ecs::World &world)
{
    world.registerSystem<ecs::MovementUpdateSystem>();
}

void bomberman::registerRender(ecs::World &world)
{
    world.registerSystem<ecs::AnimationUpdateSystem>();

    world.registerSystems<ecs::DrawTextureCubeSystem,
    ecs::DrawableModelSystem, ecs::Draw3DTextSystem, ecs::DrawGridSystem>();

    world.registerComponent<ecs::BackgroundRotation>();
    world.registerSystem<ecs::BackgroundRotationUpdateSystem>();

    world.registerComponent<ecs::Intro>();
    world.registerComponent<ecs::CameraFollow>();

    world.registerSystem<ecs::LightUpdateSystem>();
}

void bomberman::registerInputs(ecs::World &world)
{
    world.registerComponents<ecs::Clickable, ecs::Hoverable>();
    world.registerSystems<ecs::ClickUpdateSystem, ecs::HoverUpdateSystem>();

    world.registerComponent<ecs::PlayerInputs>();
    world.registerSystems<ecs::PlayerInputsUpdateSystem>();

    world.registerComponents<ecs::HoverTint, ecs::HoverRotate, ecs::SceneMoveElement>();
    world.registerSystems<ecs::HoverTintUpdateSystem, ecs::HoverRotateUpdateSystem, ecs::SceneMoveElementSystem>();

    world.registerComponents<ecs::ResolutionButton, ecs::FullscreenButton, ecs::FPSButton,
    ecs::ToggleButton, ecs::SingleKeyRecorder, ecs::TextInput, ecs::TextInputSettings, ecs::Disappear, ecs::LaunchButton>();
    world.registerSystems<ecs::ResolutionButtonSystem, ecs::FullscreenButtonSystem, ecs::FPSButtonSystem,
    ecs::ShowFPSButtonSystem, ecs::ToggleMusicButtonSystem, ecs::ToggleSoundButtonSystem,
    ecs::KeyRecorderSystem, ecs::TextInputSystem, ecs::TextInputSettingsSystem, ecs::DisappearSystem, ecs::LaunchButtonSystem>();
}

void bomberman::registerNetwork(ecs::World &world, bool client)
{
    world.registerComponents<ecs::MirrorEntity, ecs::MirroredEntity>();
    if (client) {
        world.registerSystem<ecs::ClientUpdateSystem>();
    } else {
        world.registerSystem<ecs::ServerUpdateSystem>();
    }
}
