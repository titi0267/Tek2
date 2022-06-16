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
            _close = false;
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
            if (_close)
                return (true);
            return WindowShouldClose();
        }

        Vector2 getMousePos()
        {
            return GetMousePosition();
        }

        int getFPS()
        {
            return (_fps);
        }

        void drawFPS(int x, int y)
        {
            DrawFPS(x, y);
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
            resize({(float)1920,(float)1080});
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
        private:
            bool _close;
            int _fps;
    };
}
