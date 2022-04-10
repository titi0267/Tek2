/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-alexandre.frantz
** File description:
** Sfml
*/

#include "Sfml.hpp"

Sfml::Sfml()
{
    std::cout << "Construct SFML" << std::endl;
    for (int i = 0; i < 19; i++) _butt.push_back(false);
}

Sfml::~Sfml()
{
    std::cout << "Quit window" << std::endl;
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
    for (int i = 0; i < 19; i++) _butt[i] = false;
    while (_window->pollEvent(_event)) {
        if (_event.type == sf::Event::Closed) _window->close();
        if (_event.type == sf::Event::KeyReleased) {
            if (_event.key.code == sf::Keyboard::Q) _butt[0] = true;
            if (_event.key.code == sf::Keyboard::D) _butt[1] = true;
            if (_event.key.code == sf::Keyboard::Z) _butt[2] = true;
            if (_event.key.code == sf::Keyboard::S) _butt[3] = true;
            if (_event.key.code == sf::Keyboard::F) _butt[4] = true;
            if (_event.key.code == sf::Keyboard::V) _butt[5] = true;
            if (_event.key.code == sf::Keyboard::H) _butt[6] = true;
            if (_event.key.code == sf::Keyboard::B) _butt[7] = true;
            if (_event.key.code == sf::Keyboard::T) _butt[8] = true;
            if (_event.key.code == sf::Keyboard::Y) _butt[9] = true;
            if (_event.key.code == sf::Keyboard::Return) _butt[10] = true;
            if (_event.key.code == sf::Keyboard::Space) _butt[11] = true;
            if (_event.key.code == sf::Keyboard::F1) _butt[12] = true;
            if (_event.key.code == sf::Keyboard::F2) _butt[13] = true;
            if (_event.key.code == sf::Keyboard::F3) _butt[14] = true;
            if (_event.key.code == sf::Keyboard::F4) _butt[15] = true;
            if (_event.key.code == sf::Keyboard::F5) _butt[16] = true;
            if (_event.key.code == sf::Keyboard::F6) _butt[17] = true;
            if (_event.key.code == sf::Keyboard::F7) {
                _butt[18] = true;
                _window->close();
            }
        }
    }
}

std::unique_ptr<IDisplayModule> gEpitechArcadeGetDisplayModuleHandle()
{
    return std::make_unique<Sfml>();
}