/*
** EPITECH PROJECT, 2022
** input
** File description:
** GamepadMap
*/

#include "input/GamepadBind.hpp"

const std::unordered_map<GamepadButton, std::string> buttonToString {
    std::make_pair(GAMEPAD_BUTTON_LEFT_FACE_UP, "DPAD_UP"),
    std::make_pair(GAMEPAD_BUTTON_LEFT_FACE_RIGHT, "DPAD_RIGHT"),
    std::make_pair(GAMEPAD_BUTTON_LEFT_FACE_LEFT, "DPAD_LEFT"),
    std::make_pair(GAMEPAD_BUTTON_LEFT_FACE_DOWN, "DPAD_DOWN"),
    std::make_pair(GAMEPAD_BUTTON_RIGHT_FACE_DOWN, "BUTTON_A"),
    std::make_pair(GAMEPAD_BUTTON_RIGHT_FACE_UP, "BUTTON_Y"),
    std::make_pair(GAMEPAD_BUTTON_RIGHT_FACE_LEFT, "BUTTON_X"),
    std::make_pair(GAMEPAD_BUTTON_RIGHT_FACE_RIGHT, "BUTTON_B"),
    std::make_pair(GAMEPAD_BUTTON_MIDDLE_RIGHT, "START"),
    std::make_pair(GAMEPAD_BUTTON_MIDDLE_LEFT, "SELECT"),
    std::make_pair(GAMEPAD_BUTTON_RIGHT_TRIGGER_1, "R1"),
    std::make_pair(GAMEPAD_BUTTON_RIGHT_TRIGGER_2, "R2"),
    std::make_pair(GAMEPAD_BUTTON_LEFT_TRIGGER_1, "L1"),
    std::make_pair(GAMEPAD_BUTTON_LEFT_TRIGGER_2, "L2"),
    std::make_pair((GamepadButton)GAMEPAD_JOYSTICK_RIGHT_FACE_UP, "RJOY_UP"),
    std::make_pair((GamepadButton)GAMEPAD_JOYSTICK_RIGHT_FACE_DOWN, "RJOY_DOWN"),
    std::make_pair((GamepadButton)GAMEPAD_JOYSTICK_RIGHT_FACE_RIGHT, "RJOY_RIGHT"),
    std::make_pair((GamepadButton)GAMEPAD_JOYSTICK_RIGHT_FACE_LEFT, "RJOY_LEFT"),
    std::make_pair((GamepadButton)GAMEPAD_JOYSTICK_LEFT_FACE_UP, "LJOY_UP"),
    std::make_pair((GamepadButton)GAMEPAD_JOYSTICK_LEFT_FACE_DOWN, "LJOY_DOWN"),
    std::make_pair((GamepadButton)GAMEPAD_JOYSTICK_LEFT_FACE_RIGHT, "LJOY_RIGHT"),
    std::make_pair((GamepadButton)GAMEPAD_JOYSTICK_LEFT_FACE_LEFT, "LJOY_LEFT"),
};

const std::unordered_map<GamepadButton, std::string> buttonToGameText {
    std::make_pair(GAMEPAD_BUTTON_LEFT_FACE_UP, "D^"),
    std::make_pair(GAMEPAD_BUTTON_LEFT_FACE_RIGHT, "D>"),
    std::make_pair(GAMEPAD_BUTTON_LEFT_FACE_LEFT, "D<"),
    std::make_pair(GAMEPAD_BUTTON_LEFT_FACE_DOWN, "Dv"),
    std::make_pair(GAMEPAD_BUTTON_RIGHT_FACE_DOWN, "A"),
    std::make_pair(GAMEPAD_BUTTON_RIGHT_FACE_UP, "Y"),
    std::make_pair(GAMEPAD_BUTTON_RIGHT_FACE_LEFT, "X"),
    std::make_pair(GAMEPAD_BUTTON_RIGHT_FACE_RIGHT, "B"),
    std::make_pair(GAMEPAD_BUTTON_MIDDLE_RIGHT, "START"),
    std::make_pair(GAMEPAD_BUTTON_MIDDLE_LEFT, "SELECT"),
    std::make_pair(GAMEPAD_BUTTON_RIGHT_TRIGGER_1, "R1"),
    std::make_pair(GAMEPAD_BUTTON_RIGHT_TRIGGER_2, "R2"),
    std::make_pair(GAMEPAD_BUTTON_LEFT_TRIGGER_1, "L1"),
    std::make_pair(GAMEPAD_BUTTON_LEFT_TRIGGER_2, "L2"),
    std::make_pair((GamepadButton)GAMEPAD_JOYSTICK_RIGHT_FACE_UP, "RO^"),
    std::make_pair((GamepadButton)GAMEPAD_JOYSTICK_RIGHT_FACE_DOWN, "ROv"),
    std::make_pair((GamepadButton)GAMEPAD_JOYSTICK_RIGHT_FACE_RIGHT, "RO>"),
    std::make_pair((GamepadButton)GAMEPAD_JOYSTICK_RIGHT_FACE_LEFT, "RO<"),
    std::make_pair((GamepadButton)GAMEPAD_JOYSTICK_LEFT_FACE_UP, "LO^"),
    std::make_pair((GamepadButton)GAMEPAD_JOYSTICK_LEFT_FACE_DOWN, "LOv"),
    std::make_pair((GamepadButton)GAMEPAD_JOYSTICK_LEFT_FACE_RIGHT, "LO>"),
    std::make_pair((GamepadButton)GAMEPAD_JOYSTICK_LEFT_FACE_LEFT, "LO<"),
};