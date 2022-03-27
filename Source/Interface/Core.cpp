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

}

void openWindow(ICore::Vector2u pixelsWantedWindowSize)
{

}