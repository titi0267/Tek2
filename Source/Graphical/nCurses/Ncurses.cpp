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
    endwin();
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
    noecho();
    nodelay(stdscr, true);
    curs_set(0);
    keypad(stdscr, TRUE);
    start_color();
    createPairs();
}

bool Ncurses::isButtonPressed(IDisplayModule::Button button)
{
    if (button == IDisplayModule::Button::Left && _key == 'q') return true;
    if (button == IDisplayModule::Button::Right && _key == 'd') return true;
    if (button == IDisplayModule::Button::Up && _key == 'z') return true;
    if (button == IDisplayModule::Button::Down && _key == 's') return true;
    if (button == IDisplayModule::Button::A && _key == 'f') return true;
    if (button == IDisplayModule::Button::B && _key == 'v') return true;
    if (button == IDisplayModule::Button::X && _key == 'h') return true;
    if (button == IDisplayModule::Button::Y && _key == 'b') return true;
    if (button == IDisplayModule::Button::L && _key == 't') return true;
    if (button == IDisplayModule::Button::R && _key == 'y') return true;
    if (button == IDisplayModule::Button::Start && _key == KEY_ENTER) return true;
    if (button == IDisplayModule::Button::Select && _key == ' ') return true;
    if (button == IDisplayModule::Button::F1 && _key == 265) return true;
    if (button == IDisplayModule::Button::F2 && _key == 266) return true;
    if (button == IDisplayModule::Button::F3 && _key == 267) return true;
    if (button == IDisplayModule::Button::F4 && _key == 268) return true;
    if (button == IDisplayModule::Button::F5 && _key == 269) return true;
    if (button == IDisplayModule::Button::F6 && _key == 270) return true;
    if (button == IDisplayModule::Button::F7 && _key == 271) return true;
    return false;
}

IDisplayModule::MouseButtonReleaseEvent Ncurses::getMouseButtonReleaseEvent()
{
    IDisplayModule::MouseButtonReleaseEvent mouse;
    MEVENT event;

    mouse.type = IDisplayModule::MouseButtonReleaseEvent::Type::None;
    mousemask(ALL_MOUSE_EVENTS, NULL);
    mouse.cellPosition.x = event.x;
    mouse.cellPosition.y = event.y;
    if (_key == KEY_MOUSE && getmouse(&event) == OK && event.bstate) {
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
    clear();
    wbkgd(stdscr, COLOR_PAIR(getPair(color, color)));
}

void Ncurses::createPairs()
{
    int cnt = 0;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            init_pair(cnt, i, j);
            cnt++;
        }
    }
}

int Ncurses::getPair(IDisplayModule::Color one, IDisplayModule::Color two)
{
    return ((int)one * 8 + (int)two);
}

void Ncurses::renderSprite(IDisplayModule::Sprite sprite)
{
    int color1;
    int color2;
    IRawTexture *raw = dynamic_cast<IRawTexture *>(sprite.texture);
    move(sprite.rawPixelPosition.y, sprite.rawPixelPosition.x);

    attron(COLOR_PAIR(getPair(raw->getCharColor(), raw->getBackColor())));
    addch(raw->getChar());
    attroff(COLOR_PAIR(getPair(raw->getCharColor(), raw->getBackColor())));
}

void Ncurses::display()
{
    refresh();
}

void Ncurses::update()
{
    _key = getch();
}

std::unique_ptr<IDisplayModule> gEpitechArcadeGetDisplayModuleHandle()
{
    return std::make_unique<Ncurses>();
}
