/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** PlayerInputs
*/

#pragma once

#include "raylib/Window.hpp"
#include "ecs/engine/System.hpp"
#include "ecs/engine/World.hpp"
#include "ecs/engine/PlayerId.hpp"
#include "input/InputFile.hpp"

namespace ecs {
    using Key = ::KeyboardKey;

    enum Actions {
        DO_NOTHING,
        MOVE_UP,
        MOVE_DOWN,
        MOVE_LEFT,
        MOVE_RIGHT,
        PLACE_BOMB,
    };

    struct PlayerAction {
        PlayerId id;
        Actions action = DO_NOTHING;

        PlayerAction(PlayerId id = -1) : id(id) {};
    };

    struct PlayerInputs {
        int upKey;
        int downKey;
        int leftKey;
        int rightKey;
        int bombKey;
        bool gamepad;

        public:
        PlayerInputs()
        {
            gamepad = false;
            upKey = KEY_W;
            downKey = KEY_S;
            leftKey = KEY_Q;
            rightKey = KEY_D;
            bombKey = KEY_SPACE;
        }
        PlayerInputs(InputFile &file)
        {
            gamepad = file.getGamepad();
            upKey = file.getKey(IBind::UP);
            downKey = file.getKey(IBind::DOWN);
            leftKey = file.getKey(IBind::LEFT);
            rightKey = file.getKey(IBind::RIGHT);
            bombKey = file.getKey(IBind::PLACE);
        }
    };

    class PlayerInputsUpdateSystem : public ecs::ASystem {
        public:
        PlayerInputsUpdateSystem() { _stage = ecs::Stages::INPUT_UPDATE; };

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };

    class PlayerActionUpdateSystem : public ecs::ASystem {
        public:
        PlayerActionUpdateSystem() { _stage = ecs::Stages::INPUT_UPDATE; };

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };

    class SceneActionsHandleModule {
        public:
        virtual void setPlayerAction(ecs::PlayerId id, ecs::Actions action) = 0;
        virtual ecs::Actions getPlayerAction(ecs::PlayerId id) const = 0;
        virtual bool isActionUpdatedThisFrame(ecs::PlayerId id) const = 0;
        virtual void setActionUpdatedThisFrame(ecs::PlayerId id, bool updated) = 0;
    };
}
