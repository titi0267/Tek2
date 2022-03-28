#pragma once

#include "../../arcade-interface-master/IDisplayModule.hpp"

class DisplayModule : public IDisplayModule {
    public:
        DisplayModule();
        ~DisplayModule();
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
        std::unique_ptr<DisplayModule::RawTexture> loadTexture(const std::string &filename, char character, DisplayModule::Color characterColor, DisplayModule::Color backgroundColor, std::size_t width, std::size_t height);
        void openWindow(DisplayModule::Vector2u pixelsWantedWindowSize);
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
        bool isButtonPressed(DisplayModule::Button button);
        struct MouseButtonReleaseEvent {
            enum class Type {
                None,
                Left,
                Right,
            } type;
            DisplayModule::Vector2u cellPosition;
        };
        IDisplayModule::MouseButtonReleaseEvent getMouseButtonReleaseEvent();
        bool isClosing();
        void startTextInput();
        std::string getTextInput();
        void endTextInput();
        struct Sprite {
            DisplayModule::Vector2u rawPixelPosition;
            DisplayModule::RawTexture *texture;
        };
        void clearScreen(DisplayModule::Color color);
        void renderSprite(DisplayModule::Sprite sprite);
        void display();
        void update();
};

inline DisplayModule::RawTexture::~RawTexture()
{
}

extern "C" std::unique_ptr<IDisplayModule> gEpitechArcadeGetDisplayModuleHandle();
