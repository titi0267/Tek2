/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-alexandre.frantz
** File description:
** Core
*/

#pragma once

#include "../../arcade-interface-master/ICore.hpp"
#include "../../arcade-interface-master/IDisplayModule.hpp"
#include "../../arcade-interface-master/IGameModule.hpp"
#include "../Error/Error.hpp"
#include "Texture.hpp"
#include <deque>

class Core : public ICore {
    public:
        Core();
        ~Core();
        void setPixelsPerCell(std::uint32_t pixelsPerCell);
        void setFramerate(unsigned framerate);
        using Vector2u = IDisplayModule::Vector2u;
        using Color = IDisplayModule::Color;
        using Texture = ICore::Texture;
        Core::Texture *loadTexture(const std::string &filename, char character, Core::Color characterColor, Core::Color backgroundColor, std::size_t width, std::size_t height);
        void openWindow(Core::Vector2u pixelsWantedWindowSize);
        using Button = IDisplayModule::Button;
        bool isButtonPressed(Core::Button button);
        using MouseButtonReleaseEvent = IDisplayModule::MouseButtonReleaseEvent;
        ICore::MouseButtonReleaseEvent getMouseButtonReleaseEvent();
        void startTextInput();
        std::string getTextInput();
        void endTextInput();
        void clearScreen(Core::Color color);
        void renderSprite(ICore::Sprite sprite);
        void addNewScore(std::uint32_t score);

    protected:
        Error _setError;
        std::unique_ptr<IDisplayModule> _disp;
        std::unique_ptr<IGameModule> _game;
        std::unique_ptr<Texture> _texture;
        std::deque<Texture> textureMap;
};
