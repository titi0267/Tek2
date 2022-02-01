/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGRUSH3-elliot.waldvogel
** File description:
** printInfo
*/

#include "../core.hpp"
#include <stdio.h>
#include <string.h>
#include <sys/utsname.h>

void Window::Background()
{
    _window.draw(space);
}

void Window::printName(Get_file a)
{
    text.setFillColor(sf::Color::Green);
    text.setPosition(sf::Vector2f(100, 20));
    text.setString(a.getHostname());
    _window.draw(text);
    text.setPosition(sf::Vector2f(300, 20));
    text.setString(a.getUsername());
    _window.draw(text);
}

void Window::printCpu(Get_file a)
{
    rect.setFillColor(sf::Color::Blue);
    rect.setSize(sf::Vector2f(1920, 3));
    rect.setPosition(sf::Vector2f(0, 70));
    _window.draw(rect);
    text.setColor(sf::Color::Red);
    text.setScale(2, 2);
    text.setPosition(sf::Vector2f(10, 90));
    text.setString("CPU");
    _window.draw(text);
    text.setScale(1, 1);
    text.setColor(sf::Color::Green);
    text.setPosition(sf::Vector2f(300, 110));
    text.setString("Os name :");
    _window.draw(text);
    text.setPosition(sf::Vector2f(440, 110));
    text.setString(a.getOsName());
    _window.draw(text);
    text.setPosition(sf::Vector2f(300, 150));
    text.setString("Model :");
    _window.draw(text);
    text.setPosition(sf::Vector2f(440, 150));
    text.setString(a.getModel());
    _window.draw(text);
    text.setString(a.getActivity());
    text.setPosition(sf::Vector2f(440, 190));
    _window.draw(text);
}

void Window::printInfo()
{
    Get_file a;
    struct utsname unameData;
    uname(&unameData);

    Background();
    printName(a);
    text.setString(a.getTime());
    text.setPosition(sf::Vector2f(1500, 20));
    _window.draw(text);
    printCpu(a);
}