/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-alexandre.frantz
** File description:
** DisplayModule
*/

#include "DisplayModule.hpp"

DisplayModule::DisplayModule()
{
}

DisplayModule::~DisplayModule()
{
}

void DisplayModule::setPixelsPerCell(std::uint32_t pixelsPerCell)
{
    ;
}

std::uint32_t DisplayModule::getPixelsPerCell()
{
    ;
}

std::unique_ptr<IDisplayModule::RawTexture> DisplayModule::loadTexture(const std::string &filename, char character, IDisplayModule::Color characterColor, IDisplayModule::Color backgroundColor, std::size_t width, std::size_t height)
{
    ;
}

void DisplayModule::openWindow(IDisplayModule::Vector2u pixelsWantedWindowSize)
{
    ;
}

bool DisplayModule::isButtonPressed(IDisplayModule::Button button)
{
    ;
}

IDisplayModule::MouseButtonReleaseEvent DisplayModule::getMouseButtonReleaseEvent()
{
    ;
}

bool DisplayModule::isClosing()
{
;
}

void DisplayModule::startTextInput()
{
;
}

std::string DisplayModule::getTextInput()
{
;
}

void DisplayModule::endTextInput()
{
    ;
}

void DisplayModule::clearScreen(IDisplayModule::Color color)
{
    ;
}

void DisplayModule::renderSprite(IDisplayModule::Sprite sprite)
{
    ;
}

void DisplayModule::display()
{
    ;
}


void DisplayModule::update()
{
    ;
}