/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-alexandre.frantz
** File description:
** Core
*/

#include "Core.hpp"
#include "../define.hpp"

Core::Core()
{
}

Core::~Core()
{
}

void Core::setPixelsPerCell(std::uint32_t pixelsPerCell)
{
    std::string error = "ERROR: there must be at least one pixel per cell";

    if (pixelsPerCell <= 0) {
        _setError.setReason(error);
        _setError.displayReason();
        _setError.setReturnValue(ERROR);
        _setError.exitProgram();
    }
    _disp->setPixelsPerCell(pixelsPerCell);
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

Core::Texture *Core::loadTexture(const std::string &filename, char character, Core::Color characterColor, Core::Color backgroundColor, std::size_t width, std::size_t height)
{
    ;
    //return (_disp->loadTexture(filename, character, characterColor, backgroundColor, width, height));
    /* tmp->setFilename(filename);
    tmp->setChar(character);
    tmp->setCharColor(characterColor);
    tmp->setBackColor(backgroundColor);
    tmp->setWidth(width);
    tmp->setHeight(height); */
}

void Core::openWindow(ICore::Vector2u pixelsWantedWindowSize)
{
    _disp->openWindow(pixelsWantedWindowSize);
}

bool Core::isButtonPressed(Core::Button button)
{
    return (_disp->isButtonPressed(button));
}

ICore::MouseButtonReleaseEvent Core::getMouseButtonReleaseEvent()
{
    return (_disp->getMouseButtonReleaseEvent());
}

void Core::startTextInput()
{
    _disp->startTextInput();
}

std::string Core::getTextInput()
{
    return _disp->getTextInput();
}

void Core::endTextInput()
{
    _disp->endTextInput();
}

void Core::clearScreen(Core::Color color)
{
    _disp->clearScreen(color);
}

void Core::renderSprite(ICore::Sprite sprite)
{
    IDisplayModule::Sprite sprt;
    sprt.rawPixelPosition.x = sprite.pixelPosition.x;
    sprt.rawPixelPosition.y = sprite.pixelPosition.y;
    //sprt.texture = sprite.texture.getRaw();
    _disp->renderSprite(sprt);
}

void Core::addNewScore(std::uint32_t score)
{
    (void)score;
}
