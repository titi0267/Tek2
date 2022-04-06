/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-alexandre.frantz
** File description:
** Ncurses
*/

#include "Ncurses.hpp"

Ncurses::Ncurses()
{
}

Ncurses::~Ncurses()
{
}

void Ncurses::setPixelsPerCell(std::uint32_t pixelsPerCell)
{
    _pixelsPerCell = pixelsPerCell;
}

std::uint32_t Ncurses::getPixelsPerCell()
{
    return _pixelsPerCell;
}

std::unique_ptr<IDisplayModule::RawTexture> Ncurses::loadTexture(const std::string &filename, char character, IDisplayModule::Color characterColor, IDisplayModule::Color backgroundColor, std::size_t width, std::size_t height)
{
    (void)filename;
    return std::make_unique<RawTextureNCurses>(character, characterColor, backgroundColor, width, height);
}

void Ncurses::openWindow(IDisplayModule::Vector2u pixelsWantedWindowSize)
{
    initscr();
    keypad(stdscr, TRUE);
    getmaxyx(stdscr, pixelsWantedWindowSize.y, pixelsWantedWindowSize.x);
}

bool Ncurses::isButtonPressed(IDisplayModule::Button button)
{
    int key;

    if ((key = getch()) == -1)
        _setError.exitError(ERROR, "ERROR: getch() for keyboard didn't work");
    if (button == IDisplayModule::Button::Left && key == 'q') return true;
    if (button == IDisplayModule::Button::Right && key == 'd') return true;
    if (button == IDisplayModule::Button::Up && key == 'z') return true;
    if (button == IDisplayModule::Button::Down && key == 's') return true;
    if (button == IDisplayModule::Button::A && key == 'f') return true;
    if (button == IDisplayModule::Button::B && key == 'v') return true;
    if (button == IDisplayModule::Button::X && key == 'h') return true;
    if (button == IDisplayModule::Button::Y && key == 'b') return true;
    if (button == IDisplayModule::Button::L && key == 't') return true;
    if (button == IDisplayModule::Button::R && key == 'y') return true;
    if (button == IDisplayModule::Button::Start && key == KEY_ENTER) return true;
    if (button == IDisplayModule::Button::Select && key == ' ') return true;
    if (button == IDisplayModule::Button::F1 && key == 265) return true;
    if (button == IDisplayModule::Button::F2 && key == 266) return true;
    if (button == IDisplayModule::Button::F3 && key == 267) return true;
    if (button == IDisplayModule::Button::F4 && key == 268) return true;
    if (button == IDisplayModule::Button::F5 && key == 269) return true;
    if (button == IDisplayModule::Button::F6 && key == 270) return true;
    if (button == IDisplayModule::Button::F7 && key == 271) return true;
    return false;
}

IDisplayModule::MouseButtonReleaseEvent Ncurses::getMouseButtonReleaseEvent()
{
    IDisplayModule::MouseButtonReleaseEvent mouse;
    int key;
    MEVENT event;

    if ((key = getch()) == -1)
        _setError.exitError(ERROR, "ERROR: getch() for mouse didn't work");
    mouse.type = IDisplayModule::MouseButtonReleaseEvent::Type::None;
    mousemask(ALL_MOUSE_EVENTS, NULL);
    mouse.cellPosition.x = event.x;
    mouse.cellPosition.y = event.y;
    if (key == KEY_MOUSE && getmouse(&event) == OK && event.bstate) {
        if (BUTTON1_RELEASED) mouse.type = IDisplayModule::MouseButtonReleaseEvent::Type::Left;
        else if (BUTTON2_RELEASED) mouse.type = IDisplayModule::MouseButtonReleaseEvent::Type::Right;
    }
    return mouse;
}

bool Ncurses::isClosing()
{
    return false;
}

void Ncurses::startTextInput()
{
    ;
}

std::string Ncurses::getTextInput()
{
    std::string tmp;
    return tmp;
}

void Ncurses::endTextInput()
{
    ;
}

void Ncurses::clearScreen(IDisplayModule::Color color)
{
    int bck = 0;
    clear();
    start_color();
    if (color == IDisplayModule::Color::black) bck = COLOR_BLACK;
    if (color == IDisplayModule::Color::red) bck = COLOR_RED;
    if (color == IDisplayModule::Color::green) bck = COLOR_GREEN;
    if (color == IDisplayModule::Color::yellow) bck = COLOR_YELLOW;
    if (color == IDisplayModule::Color::blue) bck = COLOR_BLUE;
    if (color == IDisplayModule::Color::magenta) bck = COLOR_MAGENTA;
    if (color == IDisplayModule::Color::cyan) bck = COLOR_CYAN;
    if (color == IDisplayModule::Color::white) bck = COLOR_WHITE;
    init_pair(1, bck, bck);
    wbkgd(stdscr, COLOR_PAIR(1));
}

void Ncurses::renderSprite(IDisplayModule::Sprite sprite)
{
    int color1;
    int color2;
    IRawTexture *raw = dynamic_cast<IRawTexture *>(sprite.texture);
    move(sprite.rawPixelPosition.y, sprite.rawPixelPosition.x);

    start_color();
    if (raw->getCharColor() == IDisplayModule::Color::red) color1 = COLOR_RED;
    if (raw->getCharColor() == IDisplayModule::Color::black) color1 = COLOR_BLACK;
    if (raw->getCharColor() == IDisplayModule::Color::green) color1 = COLOR_GREEN;
    if (raw->getCharColor() == IDisplayModule::Color::yellow) color1 = COLOR_YELLOW;
    if (raw->getCharColor() == IDisplayModule::Color::blue) color1 = COLOR_BLUE;
    if (raw->getCharColor() == IDisplayModule::Color::magenta) color1 = COLOR_MAGENTA;
    if (raw->getCharColor() == IDisplayModule::Color::cyan) color1 = COLOR_CYAN;
    if (raw->getCharColor() == IDisplayModule::Color::white) color1 = COLOR_WHITE;
    if (raw->getBackColor() == IDisplayModule::Color::black) color2 = COLOR_BLACK;
    if (raw->getBackColor() == IDisplayModule::Color::red) color2 = COLOR_RED;
    if (raw->getBackColor() == IDisplayModule::Color::green) color2 = COLOR_GREEN;
    if (raw->getBackColor() == IDisplayModule::Color::yellow) color2 = COLOR_YELLOW;
    if (raw->getBackColor() == IDisplayModule::Color::blue) color2 = COLOR_BLUE;
    if (raw->getBackColor() == IDisplayModule::Color::magenta) color2 = COLOR_MAGENTA;
    if (raw->getBackColor() == IDisplayModule::Color::cyan) color2 = COLOR_CYAN;
    if (raw->getBackColor() == IDisplayModule::Color::white) color2 = COLOR_WHITE;
    init_pair(1, color1, color2);
    attron(COLOR_PAIR(1));
    addch(raw->getChar());
    attroff(COLOR_PAIR(1));
}

void Ncurses::display()
{
    refresh();
}

void Ncurses::update()
{

}

std::unique_ptr<IDisplayModule> gEpitechArcadeGetDisplayModuleHandle()
{
    return std::make_unique<Ncurses>();
}
