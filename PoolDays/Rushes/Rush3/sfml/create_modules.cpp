/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGRUSH3-elliot.waldvogel
** File description:
** create_modules
*/
#include "sfml.hpp"

Window::Window()
{
    sf::Vector2i wnd_pos = {0, 0};

    scr_size.width = 1920;
    scr_size.height = 1080;
    scr_size.bitsPerPixel = 32;
    font.loadFromFile("arial.ttf");
    _window.setFramerateLimit(55);
    _window.create(scr_size, "My_GKrellm", sf::Style::Resize | sf::Style::Close);
    text.setFont(font);
    tex.loadFromFile("space.jpg");
    space.setTexture(tex);
}

void Window::printWindow()
{
    while (_window.isOpen()) {
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _window.close();
        }
        _window.clear();
        sleep(1);
        printInfo();
        _window.display();
    }
}

Window::~Window()
{
}

sf::RenderWindow *Window::getWindow()
{
    ;//return _window;
}
