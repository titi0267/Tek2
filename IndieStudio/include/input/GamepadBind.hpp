/*
** EPITECH PROJECT, 2022
** input
** File description:
** GamepadBind
*/

#pragma once

#include "IBind.hpp"
#include "raylib/headers/raylib.h"
#include <vector>
#include <string>
#include <unordered_map>

typedef enum {
    GAMEPAD_JOYSTICK_RIGHT_FACE_UP = 18,
    GAMEPAD_JOYSTICK_RIGHT_FACE_DOWN,
    GAMEPAD_JOYSTICK_RIGHT_FACE_RIGHT,
    GAMEPAD_JOYSTICK_RIGHT_FACE_LEFT,
    GAMEPAD_JOYSTICK_LEFT_FACE_UP,
    GAMEPAD_JOYSTICK_LEFT_FACE_DOWN,
    GAMEPAD_JOYSTICK_LEFT_FACE_RIGHT,
    GAMEPAD_JOYSTICK_LEFT_FACE_LEFT,
} GamepadButtonCompletion;

class GamepadBind : public IBind {
    public:
        GamepadBind(const std::vector<std::string> &file);
        GamepadBind();
        ~GamepadBind();
        std::string getKeyText(Binding bind);
        std::string getKeyString(Binding bind);
        int getKey(Binding bind);
        void setKey(Binding bind, int keyInt);
        int stringToKey(const std::string &str);
        std::string keyToString(int keyInt);
        std::string keyToGameTxt(int keyInt);

    protected:
        std::vector<GamepadButton> _keys;
    private:
};

extern const std::unordered_map<GamepadButton, std::string> buttonToString;
extern const std::unordered_map<GamepadButton, std::string> buttonToGameText;
