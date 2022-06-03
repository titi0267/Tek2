/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** main
*/

#include <iostream>
#include <fstream>
#include <sstream>

#include "ecs/engine/EntityCommands.hpp"

#include "raylib/Camera.hpp"
#include "raylib/Window.hpp"

#include "raylib/TextureManager.hpp"
#include "raylib/ModelManager.hpp"
#include "raylib/AnimationManager.hpp"
#include "raylib/FontManager.hpp"

#include "ecs/components/DrawableCube.hpp"
#include "ecs/components/DrawableModel.hpp"
#include "ecs/components/Hitbox.hpp"
#include "ecs/components/Clickable.hpp"
#include "ecs/components/Hoverable.hpp"
#include "ecs/components/HoverTint.hpp"
#include "ecs/components/Text3D.hpp"
#include "ecs/components/ColorTexture.hpp"

void registerBasicComponents(ecs::World &world)
{
    world.registerComponents<Transform, ecs::Hitbox>();
}

void registerRender(ecs::World &world)
{
    world.registerComponents<ecs::DrawableCube, ecs::Tint, ecs::TextureRef>();
    world.registerSystem<ecs::DrawTextureCubeSystem>();

    world.registerComponent<ecs::ModelRef>();
    world.registerSystem<ecs::DrawableModelSystem>();

    world.registerComponents<ecs::Text3D, ecs::FontRef>();
    world.registerSystem<ecs::Draw3DTextSystem>();
}

void registerMouseInputs(ecs::World &world)
{
    world.registerComponents<ecs::Clickable, ecs::Hoverable>();
    world.registerSystems<ecs::ClickUpdateSystem, ecs::HoverUpdateSystem, ecs::HoverTintUpdateSystem>();
}

void testClick(ecs::World &world, ecs::Entity entity)
{
    puts("CLICK !");
    world.getComponent<ecs::Tint>(entity) = RED;
}

ecs::EntityCommands spawnButton(Vector3 pos, Vector3 rot, std::string text, float buttonSize, ecs::World &world)
{
    Quaternion quat = QuaternionFromEuler(rot.x, rot.y, rot.z);
    Transform transform = {pos, quat, {1, 1, 1}};
    raylib::Font &font = world.getRessource<raylib::FontManager>().loadFont("./assets/fonts/emulogic.ttf");
    raylib::Texture &woodPlanks = world.getRessource<raylib::TextureManager>().loadTexture("./assets/textures/planks.png");

    return world.spawn().insert(transform,
    ecs::Text3D {text, BLACK, {0, 0, 0.06}, 12}, ecs::FontRef {&font},
    ecs::DrawableCube {{0, 0, -0.05}, {buttonSize, 0.8, 0.1}}, ecs::TextureRef {&woodPlanks}, WHITE,
    ecs::Hitbox{{-buttonSize / 2, -0.4, -0.05}, {buttonSize / 2, 0.4, 0.05}},
    ecs::Hoverable {}, ecs::Clickable {testClick});
}

class RotationTest : public ecs::ASystem {
    public:
    void setSignature(ecs::ComponentManager &component)
    {
        _signature = component.generateSignature<Transform>();
    }

    void update(ecs::World &world)
    {
        for (ecs::Entity entity : _entities) {
            Transform &transform = world.getComponent<Transform>(entity);
            Vector3 rot = QuaternionToEuler(transform.rotation);

            rot.x += PI / 16.0 / 30;
            rot.z += PI / 32.0 / 30;
            if (rot.y >= PI / 2 - 0.01)
                rot.y = -PI / 2;
            transform.rotation = QuaternionFromEuler(rot.x, rot.y, rot.z);
        }
    }
};

int main()
{
    ecs::World world{};

    registerBasicComponents(world);
    registerRender(world);
    registerMouseInputs(world);

    world.registerSystem<RotationTest>();

// ---------------------------------

    world.insertRessource<raylib::Window>();
    world.insertRessource<raylib::Camera>(Vector3 {0.0, 0.0, 2.0}, Vector3 {0.0, 0.0, -4.0});
    world.insertRessource<raylib::TextureManager>();
    world.insertRessource<raylib::ModelManager>();
    world.insertRessource<raylib::AnimationManager>();
    world.insertRessource<raylib::FontManager>();

// ---------------------------------

    spawnButton({1, -0.75, -2}, {0, 0, 0}, "Test", 3, world);
    spawnButton({1, 0.75, -2}, {0, 0, 0}, "Test 2", 4, world);

// ---------------------------------

    raylib::Window &window = world.getRessource<raylib::Window>();

    window.setTargetFPS(60);
    window.resize({1280, 720});
    while (!window.shouldClose())
        world.update();
}
