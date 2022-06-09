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

#include "Map.hpp"

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

//    world.registerSystem<RotationTest>();

// ---------------------------------

    world.insertRessource<raylib::Window>();
    world.insertRessource<raylib::Camera>(Vector3 {0.0, 0, 2.0}, Vector3 {0, 0, -4.0});
    world.insertRessource<raylib::TextureManager>();
    world.insertRessource<raylib::ModelManager>();
    world.insertRessource<raylib::AnimationManager>();
    world.insertRessource<raylib::FontManager>();

// ---------------------------------

    world.getRessource<raylib::Camera>().setPosition({0, -2, 2});
    world.getRessource<raylib::Camera>().setTarget({0, 0, -1});
    raylib::TextureManager &textureMan = world.getRessource<raylib::TextureManager>();
    raylib::ModelManager &modelMan = world.getRessource<raylib::ModelManager>();

    raylib::Model &bagModel = modelMan.loadModel("./assets/bottle.iqm");
    raylib::Texture &bagText = textureMan.loadTexture("./assets/textures/bottle.png");
    bagModel.getMaterialView(0).setTexture(MATERIAL_MAP_DIFFUSE, bagText);

    raylib::Model &tableModel = modelMan.loadModel("./assets/chair.iqm");
    raylib::Texture &tableText = textureMan.loadTexture("./assets/textures/chair.png");
    tableModel.getMaterialView(0).setTexture(MATERIAL_MAP_DIFFUSE, tableText);

    try {
        map::Map test(9, 9, 4, 2); //width | height | players | complexity
        test.print(world);
        std::cout << std::endl;
    } catch (std::invalid_argument &e) {
        std::cout << "Construction failed: " << e.what() << std::endl;
    }
    //spawnTable({-1, 0, -1}, world);
    //spawnTable({1, 2, -2}, world);

// ---------------------------------

    raylib::Window &window = world.getRessource<raylib::Window>();

    window.setTargetFPS(60);
    window.resize({1280, 720});
    while (!window.shouldClose())
        world.update();
}
