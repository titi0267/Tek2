/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGRUSH3-elliot.waldvogel
** File description:
** sfml
*/

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window/Export.hpp>
#include "../utils/get_file.hpp"

#ifndef SFML_HPP_
#define SFML_HPP_

class Window {
    public:
        Window();
        ~Window();
        void printWindow();
        sf::RenderWindow *getWindow();
        void printInfo();
        void Background();
        void printName(Get_file a);
        void printCpu(Get_file a);

    protected:
    private:
        sf::Font font;
        sf::RenderWindow _window;
        sf::VideoMode scr_size;
        sf::Vector2f pos;
        sf::Event event;
        sf::Text text;
        sf::Texture tex;
        sf::Sprite space;
        sf::RectangleShape rect;
};

#endif /* !SFML_HPP_ */
