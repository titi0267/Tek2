/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-alexandre.frantz
** File description:
** Core
*/

#include "Core.hpp"
#include "../define.hpp"

void Core::setPixelsPerCell(std::uint32_t pixelsPerCell)
{
    std::string error = "ERROR: there must be at least one pixel per cell";

    if (pixelsPerCell <= 0) {
        _setError.setReason(error);
        _setError.displayReason();
        _setError.setReturnValue(ERROR);
        _setError.exitProgram();
    }
}

void Core::setFramerate(unsigned framerate)
{
    std::string error = "ERROR: framerate set to 0";

    if (framerate == 0) {
        _setError.setReason(error);
        _setError.displayReason();
        _setError.setReturnValue(ERROR);
        _setError.exitProgram();
    } else if (framerate < 20) {
        error = "WARNING: framerate low";
        _setError.setReason(error);
        _setError.displayReason();
    }
}

ICore::Texture *Core::loadTexture(const std::string &filename, char character, ICore::Color characterColor, ICore::Color backgroundColor, std::size_t width, std::size_t height)
{
    ICore::Texture *tmp;
    (void)filename;
    (void)character;
    (void)characterColor;
    (void)backgroundColor;
    (void)width;
    (void)height;
    return tmp;
}

void Core::openWindow(ICore::Vector2u pixelsWantedWindowSize)
{
    (void)pixelsWantedWindowSize;
}

bool Core::isButtonPressed(Core::Button button)
{
    (void)button;
    return false;
}

ICore::MouseButtonReleaseEvent Core::getMouseButtonReleaseEvent()
{
    ICore::MouseButtonReleaseEvent tmp;
    return tmp;
}

void Core::startTextInput()
{

}

std::string Core::getTextInput()
{
    std::string tmp;
    return tmp;
}

void Core::endTextInput()
{

}

void Core::clearScreen(Core::Color color)
{
    (void)color;
}

void Core::renderSprite(Core::Sprite sprite)
{
    (void)sprite;
}

void Core::addNewScore(std::uint32_t score)
{
    (void)score;
}
