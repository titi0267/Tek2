/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** Window
*/

#pragma once

#include <string>
#include "headers/raylib.h"

namespace raylib {
    class Window {
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
            SetTargetFPS(fps);
        }

        void resize(Vector2 size)
        {
            SetWindowSize(size.x, size.y);
        }

        Vector2 getWindowSize()
        {
            return getWindowSize();
        }

        void toggleClose()
        {
            _close = true;
        }

        bool shouldClose()
        {
            if (_close)
                return (true);
            return WindowShouldClose();
        }

        Vector2 getMousePos()
        {
            return GetMousePosition();
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
        private:
            bool _close;
    };
}
