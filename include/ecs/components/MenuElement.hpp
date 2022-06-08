/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** MenuElement
*/

#pragma once

#include "ecs/engine/System.hpp"

#include "raylib/Window.hpp"

namespace ecs {
    enum MenuType {
        MainMenu,
        Settings,
        Graphical,
    };
    struct MenuMovement {
        Transform active;
        Transform passive;
        bool actual;
        bool right;
        float move;
        MenuMovement () {};
        MenuMovement (Transform active, Transform passive, bool actual, bool right, float move) : active(active), passive(passive), actual(actual), right(right), move(move) {};
    };
    struct MenuElement {
        MenuType *actual;
        MenuType belong;
        bool *change;
        bool travel;
        MenuMovement pos;
        MenuElement () : actual(nullptr), change(nullptr) {};
        MenuElement (MenuType *actual, MenuType belong, bool *change, MenuMovement pos) : belong(belong), actual(actual), change(change), pos(pos) {};
    };
    class MenuElementSystem : public ecs::ASystem {
        public:
            MenuElementSystem() { _stage = ecs::Stages::RENDER_UPDATE; };
            void setSignature(ecs::ComponentManager &component);
            void update(ecs::World &world);
            bool move(Vector3 &translation, bool active, MenuMovement pos);
        protected:
        private:
    };
}