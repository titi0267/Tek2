/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-alexandre.frantz
** File description:
** Core
*/

#include "Core.hpp"
#include "../define.hpp"

Core::Core(std::deque<char *> chooseLib, int chooseLibIterator) : _dl(chooseLib[chooseLibIterator])
{
    _chooseLib = chooseLib;
    _chooseLibIterator = chooseLibIterator;
    loadLibs(_dl.getLib());
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
    timespec *time;

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
    time->tv_sec = framerate;
    clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, time, NULL);
}

Core::Texture *Core::loadTexture(const std::string &filename, char character, Color characterColor, Color backgroundColor, std::size_t width, std::size_t height)
{
    Texture texture(std::move(_disp->loadTexture(filename, character, characterColor, backgroundColor, width, height)), filename, character, characterColor, backgroundColor, width, height);

    textureMap.push_back(std::move(texture));
    return (&textureMap.back());
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
    sprite;//px pos & Texture
    sprt.texture = _texture->getRaw();
    _disp->renderSprite(sprt); //px pos & Rawtexture
}

void Core::addNewScore(std::uint32_t score)
{
    (void)score;
}

void Core::loadLibs(std::unique_ptr<IDisplayModule> disp)
{
    _disp = std::move(disp);
}

void Core::loadGames(std::unique_ptr<IGameModule> game)
{
    _game = std::move(game);
}

void Core::ChooseLib()
{
    if (isButtonPressed(Core::Button::F1) == true) { //change iterator from graphic library list
        if (_chooseLibIterator > 0)
            _chooseLibIterator--;
        else if (_chooseLibIterator == 0)
            _chooseLibIterator = 2;
        _dl.close();
        _dl.open(_chooseLib[_chooseLibIterator]);
        loadLibs(_dl.getLib());
    } else if (isButtonPressed(Core::Button::F2) == true) {
        if (_chooseLibIterator == 2)
            _chooseLibIterator++;
        else if (_chooseLibIterator < 2)
            _chooseLibIterator++;
        _dl.close();
        _dl.open(_chooseLib[_chooseLibIterator]);
        loadLibs(_dl.getLib());
    }
}

void Core::gameLoop()
{
    while (_disp->isClosing()) {
        ChooseLib();

    }
}