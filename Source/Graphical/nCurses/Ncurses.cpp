/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-alexandre.frantz
** File description:
** Ncurses
*/

#include "Ncurses.hpp"

Ncurses::Ncurses() : _setError("error")
{
    for (int i = 0; i < 19; i++) _butt.push_back(false);
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
    nodelay(stdscr, true);
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    start_color();
    createPairs();
}

bool Ncurses::isButtonPressed(IDisplayModule::Button button)
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
    move(((float)sprite.rawPixelPosition.y + (float)raw->getWidth()/2)/_pixelsPerCell, ((float)sprite.rawPixelPosition.x + (float)raw->getHeight()/2)/_pixelsPerCell);

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
    for (int i = 0; i < 19; i++) _butt[i] = false;
    _key = getch();
    if (_key == 'q') _butt[0] = true;
    if (_key == 'd') _butt[1] = true;
    if (_key == 'z') _butt[2] = true;
    if (_key == 's') _butt[3] = true;
    if (_key == 'f') _butt[4] = true;
    if (_key == 'v') _butt[5] = true;
    if (_key == 'h') _butt[6] = true;
    if (_key == 'b') _butt[7] = true;
    if (_key == 't') _butt[8] = true;
    if (_key == 'y') _butt[9] = true;
    if (_key == 10) _butt[10] = true;
    if (_key == ' ') _butt[11] = true;
    if (_key == 265) _butt[12] = true;
    if (_key == 266) _butt[13] = true;
    if (_key == 267) _butt[14] = true;
    if (_key == 268) _butt[15] = true;
    if (_key == 269) _butt[16] = true;
    if (_key == 270) _butt[17] = true;
    if (_key == 271) {
        _butt[18] = true;
        endwin();
    }
}

std::unique_ptr<IDisplayModule> gEpitechArcadeGetDisplayModuleHandle()
{
    return std::make_unique<Ncurses>();
}
