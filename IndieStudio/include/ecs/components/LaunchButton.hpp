/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** LaunchButton
*/

#pragma once

#include "ecs/engine/World.hpp"
#include "input/IBind.hpp"

namespace ecs {
    struct LaunchButton {
        bool host;
        int butNum;
        bool title;
        IBind::Binding bind;
        LaunchButton() : host(false), butNum(0) {};
        LaunchButton(bool host, int butNum) : host(host), butNum(butNum), title(true), bind(IBind::UP) {};
        LaunchButton(bool host, int butNum, IBind::Binding bind) : host(host), butNum(butNum), title(false), bind(bind) {};
    };
    class LaunchButtonSystem : public ecs::ASystem {
        public:
        LaunchButtonSystem() { _stage = ecs::Stages::INPUT_UPDATE;};

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);

        protected:
        private:
    };
}
