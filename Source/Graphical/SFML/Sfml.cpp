/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-alexandre.frantz
** File description:
** Sfml
*/

#include "Sfml.hpp"

Sfml::Sfml()
{
}

Sfml::~Sfml()
{
    _window->close();
}

void Sfml::setPixelsPerCell(std::uint32_t pixelsPerCell)
{
    _pixelsPerCell = pixelsPerCell;
}

std::uint32_t Sfml::getPixelsPerCell()
{
    return _pixelsPerCell;
}

std::unique_ptr<IDisplayModule::RawTexture> Sfml::loadTexture(const std::string &filename, char character, IDisplayModule::Color characterColor, IDisplayModule::Color backgroundColor, std::size_t width, std::size_t height)
{
    (void)character;
    (void)characterColor;
    (void)backgroundColor;
    return std::make_unique<RawTextureSfml>(filename, width, height);
}

void Sfml::openWindow(IDisplayModule::Vector2u pixelsWantedWindowSize)
{
    _window = std::make_unique<sf::RenderWindow>(sf::VideoMode(pixelsWantedWindowSize.x, pixelsWantedWindowSize.y), "Arcade");

}

bool Sfml::isButtonPressed(IDisplayModule::Button button)
{
    while (_window->pollEvent(_event)) {
        if (_event.type == sf::Event::KeyPressed) {
            if (button == IDisplayModule::Button::Left && _event.key.code == sf::Keyboard::Q) return true;
            if (button == IDisplayModule::Button::Right && _event.key.code == sf::Keyboard::D) return true;
            if (button == IDisplayModule::Button::Up && _event.key.code == sf::Keyboard::Z) return true;
            if (button == IDisplayModule::Button::Down && _event.key.code == sf::Keyboard::S) return true;
            if (button == IDisplayModule::Button::A && _event.key.code == sf::Keyboard::F) return true;
            if (button == IDisplayModule::Button::B && _event.key.code == sf::Keyboard::V) return true;
            if (button == IDisplayModule::Button::X && _event.key.code == sf::Keyboard::H) return true;
            if (button == IDisplayModule::Button::Y && _event.key.code == sf::Keyboard::B) return true;
            if (button == IDisplayModule::Button::L && _event.key.code == sf::Keyboard::T) return true;
            if (button == IDisplayModule::Button::R && _event.key.code == sf::Keyboard::Y) return true;
            if (button == IDisplayModule::Button::Start && _event.key.code == sf::Keyboard::Return) return true;
            if (button == IDisplayModule::Button::Select && _event.key.code == sf::Keyboard::Space) return true;
            if (button == IDisplayModule::Button::F1 && _event.key.code == sf::Keyboard::F1) return true;
            if (button == IDisplayModule::Button::F2 && _event.key.code == sf::Keyboard::F2) return true;
            if (button == IDisplayModule::Button::F3 && _event.key.code == sf::Keyboard::F3) return true;
            if (button == IDisplayModule::Button::F4 && _event.key.code == sf::Keyboard::F4) return true;
            if (button == IDisplayModule::Button::F5 && _event.key.code == sf::Keyboard::F5) return true;
            if (button == IDisplayModule::Button::F6 && _event.key.code == sf::Keyboard::F6) return true;
            if (button == IDisplayModule::Button::F7 && _event.key.code == sf::Keyboard::F7) return true;
        }
    }
    return false;
}

IDisplayModule::MouseButtonReleaseEvent Sfml::getMouseButtonReleaseEvent()
{
    IDisplayModule::MouseButtonReleaseEvent mouse;

    mouse.type = IDisplayModule::MouseButtonReleaseEvent::Type::None;
    mouse.cellPosition.x = sf::Mouse::getPosition(*_window).x;
    mouse.cellPosition.y = sf::Mouse::getPosition(*_window).y;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) mouse.type = IDisplayModule::MouseButtonReleaseEvent::Type::Left;
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) mouse.type = IDisplayModule::MouseButtonReleaseEvent::Type::Right;
    return mouse;
}

bool Sfml::isClosing()
{
    if (_window->isOpen()) return false;
    return true;
}

void Sfml::startTextInput()
{

}

std::string Sfml::getTextInput()
{
    std::string tmp;
    return tmp;
}

void Sfml::endTextInput()
{
    ;
}

void Sfml::clearScreen(IDisplayModule::Color color)
{
    if (color == IDisplayModule::Color::black) _window->clear(sf::Color::Black);
    if (color == IDisplayModule::Color::red) _window->clear(sf::Color::Red);
    if (color == IDisplayModule::Color::blue) _window->clear(sf::Color::Blue);
    if (color == IDisplayModule::Color::cyan) _window->clear(sf::Color::Cyan);
    if (color == IDisplayModule::Color::green) _window->clear(sf::Color::Green);
    if (color == IDisplayModule::Color::magenta) _window->clear(sf::Color::Magenta);
    if (color == IDisplayModule::Color::white) _window->clear(sf::Color::White);
    if (color == IDisplayModule::Color::yellow) _window->clear(sf::Color::Yellow);
}

void Sfml::renderSprite(IDisplayModule::Sprite sprite)
{
    IRawTexture *raw = dynamic_cast<IRawTexture *>(sprite.texture);
    sf::Texture txtr;
    sf::Sprite sprt;

    txtr.loadFromFile(raw->getFilename());
    sprt.setTexture(txtr);
    sprt.setPosition(sf::Vector2f(sprite.rawPixelPosition.x, sprite.rawPixelPosition.y));
    _window->draw(sprt);
}

void Sfml::display()
{
    _window->display();
}

void Sfml::update()
{
    while (_window->pollEvent(_event)) {
        if (_event.type == sf::Event::Closed) _window->close();
    }
}

std::unique_ptr<IDisplayModule> gEpitechArcadeGetDisplayModuleHandle()
{
    return std::make_unique<Sfml>();
}