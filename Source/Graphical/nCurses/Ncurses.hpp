/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-alexandre.frantz
** File description:
** Ncurses
*/

#ifndef NCURSES_HPP_
#define NCURSES_HPP_

#include "../../../arcade-interface-master/IDisplayModule.hpp"
#include "../../Error/Error.hpp"
#include "../../define.hpp"
#include "../../Interface/RawTexture.hpp"

extern "C" {
    #include <curses.h>
    #include <ncurses.h>
}

class Ncurses : public IDisplayModule {
    public:
        Ncurses();
        ~Ncurses();

    void setPixelsPerCell(std::uint32_t pixelsPerCell);
    std::uint32_t getPixelsPerCell();
    class RawTexture {
    public:
        ~RawTexture();
    };
    std::unique_ptr<IDisplayModule::RawTexture> loadTexture(const std::string &filename, char character, IDisplayModule::Color characterColor, IDisplayModule::Color backgroundColor, std::size_t width, std::size_t height);
    void openWindow(IDisplayModule::Vector2u pixelsWantedWindowSize);
    bool isButtonPressed(IDisplayModule::Button button);
    IDisplayModule::MouseButtonReleaseEvent getMouseButtonReleaseEvent();
    bool isClosing();
    void startTextInput();
    std::string getTextInput();
    void endTextInput();
    void clearScreen(IDisplayModule::Color color);
    void renderSprite(IDisplayModule::Sprite sprite);
    void display();
    void update();
    void createPairs();
    int getPair(IDisplayModule::Color one, IDisplayModule::Color two);

    protected:
        std::uint32_t _pixelsPerCell;
        int _key;
        Error _setError;
};

#endif /* !NCURSES_HPP_ */
