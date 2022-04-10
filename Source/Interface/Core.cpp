/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-alexandre.frantz
** File description:
** Core
*/

#include "Core.hpp"
#include "../define.hpp"

Core::Core() : _setError("error")
{
    std::cout << "construct core" << std::endl;
    _getPlayerName = "Player One";
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

int Core::getFrameRate() const
{
    return _frameRate;
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
    _frameRate = framerate;
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

const std::string &Core::getPlayerName()
{
    return _getPlayerName;
}

void Core::renderSprite(ICore::Sprite sprite)
{
    IDisplayModule::Sprite sprt;

    sprt.rawPixelPosition.x = sprite.pixelPosition.x;
    sprt.rawPixelPosition.y = sprite.pixelPosition.y;
    sprt.texture = sprite.texture->getRaw();
    _disp->renderSprite(sprt);
}

void Core::addNewScore(std::uint32_t score)
{
    (void)score;
}

void Core::loadLibs(std::unique_ptr<IDisplayModule> disp)
{
    std::cout << "move disp" << std::endl;
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
        _dl.closeLib();
        _dl.openLib(_chooseLib[_chooseLibIterator]);
        loadLibs(_dl.getLib());
    } else if (isButtonPressed(Core::Button::F2) == true) {
        if (_chooseLibIterator == 2)
            _chooseLibIterator++;
        else if (_chooseLibIterator < 2)
            _chooseLibIterator++;
        _dl.closeLib();
        _dl.openLib(_chooseLib[_chooseLibIterator]);
        loadLibs(_dl.getLib());
    }
}

void Core::gameLoop(Menu *menu)
{
    timespec time;

    //time->tv_nsec = 0;
    //time->tv_sec = 0;

    while (_disp->isClosing() == false) {
        clock_gettime(CLOCK_MONOTONIC, &time);
        time.tv_nsec += (1000000000 / getFrameRate());
        if (time.tv_nsec >= 1000000000) {
            time.tv_sec += 1;
            time.tv_nsec -= 1000000000;
        }
        menu->draw();
        //_game->update();
        _disp->update();
        //_game->draw();
        _disp->display();
        ChooseLib();
        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &time, NULL);
    }
}

IGameModule *Core::getGame() const
{
    return (_game.get());
}
