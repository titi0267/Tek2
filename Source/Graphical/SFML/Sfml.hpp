/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-alexandre.frantz
** File description:
** Sfml
*/

#ifndef SFML_HPP_
#define SFML_HPP_

#include "../../../arcade-interface-master/IDisplayModule.hpp"
#include "../../Error/Error.hpp"
#include "../../define.hpp"
#include "../../Interface/RawTexture.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <deque>

class Sfml : public IDisplayModule {
    public:
        Sfml();
        ~Sfml();
        struct Vector2u {
            std::uint32_t x;
            std::uint32_t y;
        };
        enum class Color {
            black,
            red,
            green,
            yellow,
            blue,
            magenta,
            cyan,
            white,
            none,
        };
        void setPixelsPerCell(std::uint32_t pixelsPerCell);
        std::uint32_t getPixelsPerCell();
        class RawTexture {
        public:
            ~RawTexture();
        };
        std::unique_ptr<IDisplayModule::RawTexture> loadTexture(const std::string &filename, char character, IDisplayModule::Color characterColor, IDisplayModule::Color backgroundColor, std::size_t width, std::size_t height);
        void openWindow(IDisplayModule::Vector2u pixelsWantedWindowSize);
        enum class Button {
            Left,
            Right,
            Up,
            Down,
            A,
            B,
            X,
            Y,
            L,
            R,
            Start,
            Select,
            F1,
            F2,
            F3,
            F4,
            F5,
            F6,
            F7,
        };
        bool isButtonPressed(IDisplayModule::Button button);
        struct MouseButtonReleaseEvent {
            enum class Type {
                None,
                Left,
                Right,
            } type;
            IDisplayModule::Vector2u cellPosition;
        };
        IDisplayModule::MouseButtonReleaseEvent getMouseButtonReleaseEvent();
        bool isClosing();
        void startTextInput();
        std::string getTextInput();
        void endTextInput();
        struct Sprite {
            IDisplayModule::Vector2u rawPixelPosition;
            IDisplayModule::RawTexture *texture;
        };
        void clearScreen(IDisplayModule::Color color);
        void renderSprite(IDisplayModule::Sprite sprite);
        void display();
        void update();

    protected:
        std::uint32_t _pixelsPerCell;
        std::unique_ptr<sf::RenderWindow> _window;
        sf::Event _event;
        Error _setError;
        std::deque<bool> _butt;
};

#endif /* !SFML_HPP_ */
