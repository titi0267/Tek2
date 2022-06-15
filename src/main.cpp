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
#include "ecs/engine/SceneManager.hpp"
#include "ecs/engine/Network.hpp"
#include "ecs/engine/InternalServer.hpp"
#include "ecs/engine/Clock.hpp"

#include "raylib/Camera.hpp"
#include "raylib/Window.hpp"
#include "raylib/TextureManager.hpp"
#include "raylib/ModelManager.hpp"
#include "raylib/AnimationManager.hpp"
#include "raylib/FontManager.hpp"
#include "raylib/ShaderManager.hpp"

#include "Setup.hpp"
#include "Assets.hpp"
#include "Map.hpp"

int main(int ac, char **av)
{
    #ifdef _WIN32
    if (bomberman::WSA())
        return (84);
    #endif

    ecs::World world{};

// ---- [COMPONENTS + SYSTEMS] ----

    bomberman::registerCriticalComponents(world);

    bomberman::registerInputs(world);
    bomberman::registerRender(world);
    bomberman::registerNetwork(world, true);
    bomberman::registerPhysics(world);

// ----- [GLOBAL RESSOURCES] -----

    world.insertRessource<raylib::Window>();
    world.insertRessource<raylib::Camera>(Vector3 {0.0, 0.0, 2.0}, Vector3 {0, 0, 0});
    world.insertRessource<ecs::Clock>();

    world.insertRessource<raylib::TextureManager>();
    world.insertRessource<raylib::ModelManager>();
    world.insertRessource<raylib::AnimationManager>();
    world.insertRessource<raylib::FontManager>();
    world.insertRessource<raylib::ShaderManager>();
    world.insertRessource<ecs::SceneManager>();

    world.insertRessource<ecs::ClientManager>();
    world.insertRessource<ecs::InternalServer>();

// ----- [INIT RESSOURCES] -----

    bomberman::loadTextures(world);
    bomberman::loadModels(world);
    bomberman::loadAnimations(world);
    bomberman::loadFonts(world);
    bomberman::loadShaders(world);

    bomberman::applyAssetsToModels(world);

// ------ [START + RUN GAME] ------

    world.getRessource<ecs::SceneManager>().loadDefaultScene(world);

    raylib::Window &window = world.getRessource<raylib::Window>();
    ecs::Clock &clock = world.getRessource<ecs::Clock>();

    window.setTargetFPS(60);
    window.resize({1280, 720});
    while (!window.shouldClose()) {
        clock.update();
        world.updateClient();
    }

    world.getRessource<ecs::ClientManager>().disconnect();
    world.getRessource<ecs::InternalServer>().joinAndDestroy();
}
