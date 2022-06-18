/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** Window
*/

#pragma once

#include <string>
#include "headers/raylib.h"
#include "input/GamepadBind.hpp"

namespace raylib {
    class Window {
        bool _close = false;
        int _fps;

        public:
        Window(int width = 640, int height = 480, const std::string &name = "Indie Studio")
        {
            InitWindow(width, height, name.c_str());
        };

        ~Window()
        {
            CloseWindow();
        }

        void setTargetFPS(int fps)
        {
            _fps = fps;
            SetTargetFPS(fps);
        }

        int getFPS()
        {
            return (_fps);
        }

        void drawFPS(int x, int y)
        {
            DrawFPS(x, y);
        }

        void resize(Vector2 size)
        {
            if (IsWindowFullscreen())
                return;
            SetWindowSize(size.x, size.y);
        }

        Vector2 getWindowSize()
        {
            Vector2 ret = {(float)GetScreenWidth(), (float)GetScreenHeight()};
            return (ret);
        }

        void toggleClose()
        {
            _close = true;
        }

        bool shouldClose()
        {
            return _close || WindowShouldClose();
        }

        Vector2 getMousePos()
        {
            return GetMousePosition();
        }

        bool isKeyDown(KeyboardKey key)
        {
            return IsKeyDown(key);
        }

        bool isButtonDown(int gamepad, GamepadButton button)
        {
            if (button < 18)
                return IsGamepadButtonDown(gamepad, button);
            if (button >= 18 && button <= 21) {
                float a = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X);
                float b = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y);
                if (a > 0.25 || a < -0.25 || b > 0.25 || b < -0.25) {
                    float abs_a = a < 0 ? a * -1 : a;
                    float abs_b = b < 0 ? b * -1 : b;
                    if (abs_a >= abs_b) {
                    if (a < 0)
                        return (button == (GamepadButton)GAMEPAD_JOYSTICK_LEFT_FACE_LEFT ? true : false);
                    return (button == (GamepadButton)GAMEPAD_JOYSTICK_LEFT_FACE_RIGHT ? true : false);
                    }
                    if (b < 0)
                        return (button == (GamepadButton)GAMEPAD_JOYSTICK_LEFT_FACE_UP ? true : false);
                    return (button == (GamepadButton)GAMEPAD_JOYSTICK_LEFT_FACE_DOWN ? true : false);
                }
                return (false);
            }
            float a = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_X);
            float b = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_Y);
            if (a > 0.25 || a < -0.25 || b > 0.25 || b < -0.25) {
                float abs_a = a < 0 ? a * -1 : a;
                float abs_b = b < 0 ? b * -1 : b;
                if (abs_a >= abs_b) {
                if (a < 0)
                    return (button == (GamepadButton)GAMEPAD_JOYSTICK_RIGHT_FACE_LEFT ? true : false);
                return (button == (GamepadButton)GAMEPAD_JOYSTICK_RIGHT_FACE_RIGHT ? true : false);
                }
                if (b < 0)
                    return (button == (GamepadButton)GAMEPAD_JOYSTICK_RIGHT_FACE_UP ? true : false);
                return (button == (GamepadButton)GAMEPAD_JOYSTICK_RIGHT_FACE_DOWN ? true : false);
            }
            return (false);
        }

        bool isKeyPressed(KeyboardKey key)
        {
            return IsKeyPressed(key);
        }

        bool isMouseButtonPressed(MouseButton button)
        {
            return IsMouseButtonPressed(button);
        }

        void beginDrawing()
        {
            BeginDrawing();
        }

        void endDrawing()
        {
            EndDrawing();
        }

        void clear(Color color)
        {
            ClearBackground(color);
        }

        void setFullscreen()
        {
            if (IsWindowFullscreen())
                return;
            resize({(float) 1920,(float) 1080});
            ToggleFullscreen();
        }

        bool isFullscreen()
        {
            return (IsWindowFullscreen());
        }

        void setWindowed()
        {
            if (!IsWindowFullscreen())
                return;
            ToggleFullscreen();
        }

        int getKeyPressed()
        {
            return (GetKeyPressed());
        }

        int getButtonPressed(int gamepad)
        {
            if (!IsGamepadAvailable(gamepad))
                return (0);
            float a = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X);
            float b = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y);
            float c = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_X);
            float d = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_Y);
            if (a > 0.25 || a < -0.25 || b > 0.25 || b < -0.25) {
                float abs_a = a < 0 ? a * -1 : a;
                float abs_b = b < 0 ? b * -1 : b;
                if (abs_a >= abs_b) {
                    if (a < 0)
                        return (GAMEPAD_JOYSTICK_LEFT_FACE_LEFT);
                    return (GAMEPAD_JOYSTICK_LEFT_FACE_RIGHT);
                }
                if (b < 0)
                    return (GAMEPAD_JOYSTICK_LEFT_FACE_UP);
                return (GAMEPAD_JOYSTICK_LEFT_FACE_DOWN);
            }
            if (c > 0.25 || c < -0.25 || d > 0.25 || d < -0.25) {
                float abs_c = c < 0 ? c * -1 : c;
                float abs_d = d < 0 ? d * -1 : d;
                if (abs_c >= abs_d) {
                    if (c < 0)
                        return (GAMEPAD_JOYSTICK_RIGHT_FACE_LEFT);
                    return (GAMEPAD_JOYSTICK_RIGHT_FACE_RIGHT);
                }
                if (d < 0)
                    return (GAMEPAD_JOYSTICK_RIGHT_FACE_UP);
                return (GAMEPAD_JOYSTICK_RIGHT_FACE_DOWN);
            }
            return (GetGamepadButtonPressed());
        }
        void setLogo(const std::string &path)
        {
            SetWindowIcon(LoadImage(path.c_str()));
        }
    };
}
