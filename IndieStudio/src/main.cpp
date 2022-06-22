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
#include "ecs/engine/LaunchManager.hpp"

#include "input/BindsManager.hpp"

#include "network/SocketError.hpp"

#include "raylib/Camera.hpp"
#include "raylib/Window.hpp"
#include "raylib/TextureManager.hpp"
#include "raylib/ModelManager.hpp"
#include "raylib/AnimationManager.hpp"
#include "raylib/FontManager.hpp"
#include "raylib/ShaderManager.hpp"
#include "raylib/SoundManager.hpp"

#include "Setup.hpp"
#include "Assets.hpp"
#include "Map.hpp"

int startGame(void)
{
    #ifdef _WIN32
    if (bomberman::WSA())
        return (84);
    #endif

    ecs::World world{};

// ---- [COMPONENTS + SYSTEMS] ----

    bomberman::registerCriticalComponents(world);
    bomberman::registerBothSide(world);

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
    world.insertRessource<raylib::SoundManager>();
    world.insertRessource<ecs::SceneManager>();
    world.insertRessource<ecs::BindManager>();

    world.insertRessource<ecs::ClientManager>();
    world.insertRessource<ecs::InternalServer>();
    world.insertRessource<ecs::LaunchManager>();

// ----- [INIT RESSOURCES] -----

    bomberman::loadTextures(world);
    bomberman::loadModels(world);
    bomberman::loadAnimations(world);
    bomberman::loadFonts(world);
    bomberman::loadShaders(world);
    bomberman::loadSounds(world);

    bomberman::applyAssetsToModels(world);

// ------ [START + RUN GAME] ------

    world.getRessource<ecs::SceneManager>().loadDefaultScene(world);

    raylib::Window &window = world.getRessource<raylib::Window>();
    ecs::Clock &clock = world.getRessource<ecs::Clock>();

    window.setLogo("./assets/bombitek.png");
    window.setTargetFPS(60);
    window.resize({1280, 720});
    while (!window.shouldClose()) {
        clock.update();
        world.updateClient();
    }

    world.getRessource<ecs::ClientManager>().disconnect();
    world.getRessource<ecs::InternalServer>().joinAndDestroy();

    return 0;
}

int main(int ac, char **av)
{
    try {
        return startGame();
    } catch (network::SocketError) {
        std::cerr << "Critical error related to network occured" << std::endl;
        return 84;
    } catch(std::exception &e) {
        std::cerr << "Critical error occur:\n" << e.what() << std::endl;
        return 84;
    } catch(...) {
        std::cerr << "Critical error occur !" << std::endl;
        return 84;
    }
}
