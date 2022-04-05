/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-alexandre.frantz
** File description:
** Ncurses
*/

#include "Ncurses.hpp"

Ncurses::Ncurses()
{
}

Ncurses::~Ncurses()
{
}

void Ncurses::setPixelsPerCell(std::uint32_t pixelsPerCell)
{
    _pixelsPerCell = pixelsPerCell;
}

std::uint32_t Ncurses::getPixelsPerCell()
{
    return _pixelsPerCell;
}

std::unique_ptr<IDisplayModule::RawTexture> Ncurses::loadTexture(const std::string &filename, char character, IDisplayModule::Color characterColor, IDisplayModule::Color backgroundColor, std::size_t width, std::size_t height)
{
    std::unique_ptr<IDisplayModule::RawTexture> tmp;
    (void)filename;
    (void)character;
    (void)characterColor;
    (void)backgroundColor;
    (void)width;
    (void)height;
    return tmp;
}

void Ncurses::openWindow(IDisplayModule::Vector2u pixelsWantedWindowSize)
{
    initscr();
    keypad(stdscr, TRUE);
}

bool Ncurses::isButtonPressed(IDisplayModule::Button button)
{
    int key;

    if ((key = getch()) == -1)
        _setError.exitError(ERROR, "ERROR: getch() for keyboard didn't work");
    if (button == IDisplayModule::Button::Left && key == 'q') return true;
    if (button == IDisplayModule::Button::Right && key == 'd') return true;
    if (button == IDisplayModule::Button::Up && key == 'z') return true;
    if (button == IDisplayModule::Button::Down && key == 's') return true;
    if (button == IDisplayModule::Button::A && key == 'f') return true;
    if (button == IDisplayModule::Button::B && key == 'v') return true;
    if (button == IDisplayModule::Button::X && key == 'h') return true;
    if (button == IDisplayModule::Button::Y && key == 'b') return true;
    if (button == IDisplayModule::Button::L && key == 't') return true;
    if (button == IDisplayModule::Button::R && key == 'y') return true;
    if (button == IDisplayModule::Button::Start && key == KEY_ENTER) return true;
    if (button == IDisplayModule::Button::Select && key == ' ') return true;
    if (button == IDisplayModule::Button::F1 && key == 265) return true;
    if (button == IDisplayModule::Button::F2 && key == 266) return true;
    if (button == IDisplayModule::Button::F3 && key == 267) return true;
    if (button == IDisplayModule::Button::F4 && key == 268) return true;
    if (button == IDisplayModule::Button::F5 && key == 269) return true;
    if (button == IDisplayModule::Button::F6 && key == 270) return true;
    if (button == IDisplayModule::Button::F7 && key == 271) return true;
    return false;
}

IDisplayModule::MouseButtonReleaseEvent Ncurses::getMouseButtonReleaseEvent()
{
    /* IDisplayModule::MouseButtonReleaseEvent mouse;
    int key;
    MEVENT event;

    if ((key = getch()) == -1)
        _setError.exitError(ERROR, "ERROR: getch() for mouse didn't work");
    
    if (key != KEY_MOUSE)
        mouse.type = IDisplayModule::MouseButtonReleaseEvent::Type::None;
        return mouse; */
}

bool Ncurses::isClosing()
{
    return true;
}

void Ncurses::startTextInput()
{

}

std::string Ncurses::getTextInput()
{
    std::string tmp;
    return tmp;
}

void Ncurses::endTextInput()
{
    ;
}

void Ncurses::clearScreen(IDisplayModule::Color color)
{
    (void)color;
}

void Ncurses::renderSprite(IDisplayModule::Sprite sprite)
{
    (void)sprite;
}

void Ncurses::display()
{

}

void Ncurses::update()
{

}

std::unique_ptr<IDisplayModule> gEpitechArcadeGetDisplayModuleHandle()
{
    return std::make_unique<Ncurses>();
}
