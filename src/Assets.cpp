/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** Assets
*/

#include "Assets.hpp"
#include "raylib/TextureManager.hpp"
#include "raylib/ModelManager.hpp"
#include "raylib/AnimationManager.hpp"
#include "raylib/FontManager.hpp"
#include "raylib/ShaderManager.hpp"
#include "raylib/SoundManager.hpp"

void bomberman::loadTextures(ecs::World &world)
{
    raylib::TextureManager &textureMan = world.getRessource<raylib::TextureManager>();

    textureMan.loadTexture("logo", "./assets/textures/logo.png");
    textureMan.loadTexture("epitech", "./assets/textures/epitech.png");
    textureMan.loadTexture("button", "./assets/textures/button.png");
    textureMan.loadTexture("large_button", "./assets/textures/large_button.png");
    textureMan.loadTexture("square_button", "./assets/textures/square_button.png");
    textureMan.loadTexture("amphi", "./assets/textures/amphi.png");

    textureMan.loadTexture("bottle", "./assets/textures/bottle.png");
    textureMan.loadTexture("table", "./assets/textures/table.png");
    textureMan.loadTexture("chair", "./assets/textures/chair.png");
    textureMan.loadTexture("bag", "./assets/textures/bag.png");
    // textureMan.loadTexture("ground", "./assets/textures/ground.png");
    textureMan.loadTexture("water", "./assets/textures/water.png");

    textureMan.loadTexture("timothe", "./assets/textures/timothe.png");
    textureMan.loadTexture("ludovic", "./assets/textures/ludovic.png");
    textureMan.loadTexture("mathieu", "./assets/textures/mathieu.png");
    textureMan.loadTexture("jeffrey", "./assets/textures/jeffrey.png");
    textureMan.loadTexture("tom", "./assets/textures/tom.png");
    textureMan.loadTexture("omar", "./assets/textures/omar.png");

    textureMan.loadTexture("bonus_bomb", "./assets/textures/bombBonus.png");
    textureMan.loadTexture("bonus_boots", "./assets/textures/boots.png");
    textureMan.loadTexture("bonus_range", "./assets/textures/explode.png");
    textureMan.loadTexture("bonus_tig", "./assets/textures/tig.png");
}

void bomberman::loadModels(ecs::World &world)
{
    raylib::ModelManager &modelMan = world.getRessource<raylib::ModelManager>();

    modelMan.loadModel("button", "./assets/models/button.iqm");
    modelMan.loadModel("large_button", "./assets/models/large_button.iqm");
    modelMan.loadModel("square_button", "./assets/models/square_button.iqm");
    modelMan.loadModel("logo", "./assets/models/logo.iqm");
    modelMan.loadModel("amphi", "./assets/models/amphi.iqm");

    modelMan.loadModel("bottle", "./assets/models/bottle.iqm");
    modelMan.loadModel("table", "./assets/models/table.iqm");
    modelMan.loadModel("chair", "./assets/models/chair.iqm");
    modelMan.loadModel("bag", "./assets/models/bag.iqm");
    modelMan.loadModel("water", "./assets/models/water.iqm");

    modelMan.loadModel("player", "./assets/models/player.iqm");
    modelMan.loadModel("omar", "./assets/models/omar.iqm");

    modelMan.loadModel("bonus_bomb", "./assets/models/bombBonus.iqm");
    modelMan.loadModel("bonus_boots", "./assets/models/boots.iqm");
    modelMan.loadModel("bonus_range", "./assets/models/explode.iqm");
    modelMan.loadModel("bonus_tig", "./assets/models/tig.iqm");
}

void bomberman::loadAnimations(ecs::World &world)
{
    raylib::AnimationManager &animMan = world.getRessource<raylib::AnimationManager>();

    animMan.loadAnimations("playerAnims", "./assets/models/player.iqm");
}

void bomberman::loadFonts(ecs::World &world)
{
    raylib::FontManager &fontMan = world.getRessource<raylib::FontManager>();

    fontMan.loadFont("emulogic", "./assets/fonts/emulogic.ttf");
}

void bomberman::loadShaders(ecs::World &world)
{
    raylib::ShaderManager &shaderMan = world.getRessource<raylib::ShaderManager>();

    shaderMan.loadShader("light", "./assets/shaders/lighting.vs", "./assets/shaders/lighting.fs");
}

void bomberman::loadSounds(ecs::World &world)
{
    raylib::SoundManager &soundMan = world.getRessource<raylib::SoundManager>();

    soundMan.loadSound("main_menu_music", "./assets/sounds/main_menu.mp3", true);
    soundMan.loadSound("omar_voice", "./assets/sounds/omar.wav", true);
}

void bomberman::applyAssetsToModels(ecs::World &world)
{
    raylib::TextureManager &textureMan = world.getRessource<raylib::TextureManager>();
    raylib::ModelManager &modelMan = world.getRessource<raylib::ModelManager>();
    raylib::ShaderManager &shaderMan = world.getRessource<raylib::ShaderManager>();

    modelMan.getModel("logo").getMaterialView(0)
    .setTexture(textureMan.getTexture("logo"));

    modelMan.getModel("large_button").getMaterialView(0)
    .setTexture(textureMan.getTexture("large_button"));

    modelMan.getModel("square_button").getMaterialView(0)
    .setTexture(textureMan.getTexture("square_button"));

    modelMan.getModel("button").getMaterialView(0)
    .setTexture(textureMan.getTexture("button"));

    modelMan.getModel("amphi").getMaterialView(0)
    .setTexture(textureMan.getTexture("amphi"))
    .setShader(shaderMan.getShader("light"));

    modelMan.getModel("bottle").getMaterialView(0)
    .setTexture(textureMan.getTexture("bottle"))
    .setShader(shaderMan.getShader("light"));

    modelMan.getModel("table").getMaterialView(0)
    .setTexture(textureMan.getTexture("table"))
    .setShader(shaderMan.getShader("light"));

    modelMan.getModel("chair").getMaterialView(0)
    .setTexture(textureMan.getTexture("chair"))
    .setShader(shaderMan.getShader("light"));

    modelMan.getModel("bag").getMaterialView(0)
    .setTexture(textureMan.getTexture("bag"))
    .setShader(shaderMan.getShader("light"));

    modelMan.getModel("water").getMaterialView(0)
    .setTexture(textureMan.getTexture("water"));

    modelMan.getModel("player").getMaterialView(0)
    .setTexture(textureMan.getTexture("timothe"))
    .setShader(shaderMan.getShader("light"));

    modelMan.getModel("bonus_bomb").getMaterialView(0).
    setTexture(textureMan.getTexture("bonus_bomb"))
    .setShader(shaderMan.getShader("light"));

    modelMan.getModel("bonus_boots").getMaterialView(0).
    setTexture(textureMan.getTexture("bonus_boots"))
    .setShader(shaderMan.getShader("light"));

    modelMan.getModel("bonus_range").getMaterialView(0).
    setTexture(textureMan.getTexture("bonus_range"))
    .setShader(shaderMan.getShader("light"));

    modelMan.getModel("bonus_tig").getMaterialView(0).
    setTexture(textureMan.getTexture("bonus_tig"))
    .setShader(shaderMan.getShader("light"));

    modelMan.getModel("omar").getMaterialView(0).
    setTexture(textureMan.getTexture("omar"));
}
