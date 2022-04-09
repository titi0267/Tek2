/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-alexandre.frantz
** File description:
** Sdl2
*/

#include "Sdl2.hpp"

Sdl2::Sdl2()
{
    int flag = IMG_INIT_JPG | IMG_INIT_PNG;

    if (IMG_Init(flag) == -1) _setError.exitError(ERROR, "ERROR: couldn't open Sdl2 image.");
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0) _setError.exitError(ERROR, "ERROR: couldn't open Sdl2.");
    for (int i = 0; i < 19; i++) _butt.push_back(false);
    _isClosing = false;
}

Sdl2::~Sdl2()
{
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_renderer);
    SDL_Quit();
    _isClosing = true;
}

void Sdl2::setPixelsPerCell(std::uint32_t pixelsPerCell)
{
    _pixelsPerCell = pixelsPerCell;
}

std::uint32_t Sdl2::getPixelsPerCell()
{
    return _pixelsPerCell;
}

std::unique_ptr<IDisplayModule::RawTexture> Sdl2::loadTexture(const std::string &filename, char character, IDisplayModule::Color characterColor, IDisplayModule::Color backgroundColor, std::size_t width, std::size_t height)
{
    (void)filename;
    (void)width;
    (void)height;
    return std::make_unique<RawTextureSdl2>(filename, width, height);
}

void Sdl2::openWindow(IDisplayModule::Vector2u pixelsWantedWindowSize)
{
    _window = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, pixelsWantedWindowSize.x, pixelsWantedWindowSize.y, 0);
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (!_window) _setError.exitError(ERROR, "ERROR: sdl2 window didn't open.");
}

bool Sdl2::isButtonPressed(IDisplayModule::Button button)
{
    if (button == IDisplayModule::Button::Left) return _butt[0];
    if (button == IDisplayModule::Button::Right) return _butt[1];
    if (button == IDisplayModule::Button::Up) return _butt[2];
    if (button == IDisplayModule::Button::Down) return _butt[3];
    if (button == IDisplayModule::Button::A) return _butt[4];
    if (button == IDisplayModule::Button::B) return _butt[5];
    if (button == IDisplayModule::Button::X) return _butt[6];
    if (button == IDisplayModule::Button::Y) return _butt[7];
    if (button == IDisplayModule::Button::L) return _butt[8];
    if (button == IDisplayModule::Button::R) return _butt[9];
    if (button == IDisplayModule::Button::Start) return _butt[10];
    if (button == IDisplayModule::Button::Select) return _butt[11];
    if (button == IDisplayModule::Button::F1) return _butt[12];
    if (button == IDisplayModule::Button::F2) return _butt[13];
    if (button == IDisplayModule::Button::F3) return _butt[14];
    if (button == IDisplayModule::Button::F4) return _butt[15];
    if (button == IDisplayModule::Button::F5) return _butt[16];
    if (button == IDisplayModule::Button::F6) return _butt[17];
    if (button == IDisplayModule::Button::F7) return _butt[18];
    return false;
}

IDisplayModule::MouseButtonReleaseEvent Sdl2::getMouseButtonReleaseEvent()
{
    IDisplayModule::MouseButtonReleaseEvent mouse;

    mouse.type = IDisplayModule::MouseButtonReleaseEvent::Type::None;
    mouse.cellPosition.x = _mouse.x;
    mouse.cellPosition.y = _mouse.y;
    if (_mouse.state == SDL_RELEASED) {
        if (_mouse.button == SDL_BUTTON_LEFT) mouse.type = IDisplayModule::MouseButtonReleaseEvent::Type::Left;
        else if (_mouse.button == SDL_BUTTON_RIGHT) mouse.type = IDisplayModule::MouseButtonReleaseEvent::Type::Right;
    }
    return mouse;
}

bool Sdl2::isClosing()
{
    return _isClosing;
}

void Sdl2::startTextInput()
{

}

std::string Sdl2::getTextInput()
{
    std::string tmp;
    return tmp;
}

void Sdl2::endTextInput()
{
    ;
}

void Sdl2::clearScreen(IDisplayModule::Color color)
{
    if (color == IDisplayModule::Color::black) SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    if (color == IDisplayModule::Color::red) SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
    if (color == IDisplayModule::Color::blue) SDL_SetRenderDrawColor(_renderer, 0, 0, 255, 255);
    if (color == IDisplayModule::Color::cyan) SDL_SetRenderDrawColor(_renderer, 0, 255, 255, 255);
    if (color == IDisplayModule::Color::green) SDL_SetRenderDrawColor(_renderer, 0, 255, 0, 255);
    if (color == IDisplayModule::Color::magenta) SDL_SetRenderDrawColor(_renderer, 255, 0, 255, 255);
    if (color == IDisplayModule::Color::white) SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
    if (color == IDisplayModule::Color::yellow) SDL_SetRenderDrawColor(_renderer, 255, 255, 0, 255);
    SDL_RenderClear(_renderer);
}

void Sdl2::renderSprite(IDisplayModule::Sprite sprite)
{
    IRawTexture *raw = dynamic_cast<IRawTexture *>(sprite.texture);
    SDL_Surface *sprt = IMG_Load(raw->getFilename().c_str());
    SDL_Texture *txtr = SDL_CreateTextureFromSurface(_renderer, sprt);
    SDL_Rect rect = {(int)sprite.rawPixelPosition.x, (int)sprite.rawPixelPosition.y, (int)raw->getWidth(), (int)raw->getHeight()};
    if (!sprt) std::cout << "Help!" << std::endl;
    SDL_RenderCopy(_renderer, txtr, NULL, &rect);
}

void Sdl2::display()
{
    SDL_RenderPresent(_renderer);
}

void Sdl2::update()
{
    for (int i = 0; i < 19; i++) _butt[i] = false;
    while (SDL_PollEvent(&_event)) {
        if (_event.type == SDL_WINDOWEVENT && _event.window.event == SDL_WINDOWEVENT_CLOSE) {
            SDL_DestroyWindow(_window);
            SDL_Quit();
            _isClosing = true;
        }
        if (_event.type == SDL_SCANCODE_Q) _butt[0] = true;
        if (_event.type == SDL_SCANCODE_D) _butt[1] = true;
        if (_event.type == SDL_SCANCODE_Z) _butt[2] = true;
        if (_event.type == SDL_SCANCODE_S) _butt[3] = true;
        if (_event.type == SDL_SCANCODE_F) _butt[4] = true;
        if (_event.type == SDL_SCANCODE_V) _butt[5] = true;
        if (_event.type == SDL_SCANCODE_H) _butt[6] = true;
        if (_event.type == SDL_SCANCODE_B) _butt[7] = true;
        if (_event.type == SDL_SCANCODE_T) _butt[8] = true;
        if (_event.type == SDL_SCANCODE_Y) _butt[9] = true;
        if (_event.type == SDL_SCANCODE_RETURN) _butt[10] = true;
        if (_event.type == SDL_SCANCODE_SPACE) _butt[11] = true;
        if (_event.type == SDL_SCANCODE_F1) _butt[12] = true;
        if (_event.type == SDL_SCANCODE_F2) _butt[13] = true;
        if (_event.type == SDL_SCANCODE_F3) _butt[14] = true;
        if (_event.type == SDL_SCANCODE_F4) _butt[15] = true;
        if (_event.type == SDL_SCANCODE_F5) _butt[16] = true;
        if (_event.type == SDL_SCANCODE_F6) _butt[17] = true;
        if (_event.type == SDL_SCANCODE_F7) {
            _butt[18] = true;
            SDL_DestroyWindow(_window);
            SDL_Quit();
            _isClosing = true;
        }
        if (_event.type == SDL_MOUSEBUTTONUP && _event.button.state == SDL_RELEASED) _mouse = _event.button;
    }
}

std::unique_ptr<IDisplayModule> gEpitechArcadeGetDisplayModuleHandle()
{
    return std::make_unique<Sdl2>();
}