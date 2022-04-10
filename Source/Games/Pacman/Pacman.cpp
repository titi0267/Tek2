/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-alexandre.frantz
** File description:
** Pacman
*/

#include "Pacman.hpp"
#include <algorithm>

Pacman::Pacman()
{
    _frameRate = 0;
    _ghostFrameRate = 0;
    _pacmanHead = 18;
    _pacGumEat = 0;
    _ghost1Direction = 3;
    _ghostOut = 0;
    _timer = 0;
    _direction = 3;
    _map.clear();
    _ghostOutHouse.clear();
    _ghostInHouse.clear();
    _ghostInHouse.push_back("orange");
    _ghostInHouse.push_back("pink");
    _ghostInHouse.push_back("blue");
    _ghostInHouse.push_back("red");
    _status = false;
    _orangeStatus = false;
    _redStatus = false;
    _pinkStatus = false;
    _score = 0;
    _blueStatus = false;
    _tmp = 1;
    _runner = false;
    _runnerCounter = 0;
    constructMap();
}

Pacman::~Pacman()
{
}

void Pacman::init(ICore *coreHandle)
{
    ICore::Vector2u windowsSize{624, 320};
    ICore::Vector2u border{0, 0};
    ICore::Vector2u pacman{19, 12};
    ICore::Vector2u ghost1{18, 10};
    ICore::Vector2u ghost2{19, 10};
    ICore::Vector2u ghost3{20, 10};
    ICore::Vector2u ghost4{19, 8};
    ICore::Vector2u mainText{13, 0};
    ICore::Vector2u score{0, 0};

    coreHandle->openWindow(windowsSize);
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Border/cornerBotLeft.png", '#', ICore::Color::black, ICore::Color::black, 16, 16)});
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Border/cornerBotRight.png", '#', ICore::Color::black, ICore::Color::black, 16, 16)});
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Border/cornerTopLeft.png", '#', ICore::Color::black, ICore::Color::black, 16, 16)});
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Border/cornerTopRight.png", '#', ICore::Color::black, ICore::Color::black, 16, 16)});
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Border/wallVertical.png", '#', ICore::Color::black, ICore::Color::black, 16, 16)});
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Border/wallHorizon.png", '#', ICore::Color::black, ICore::Color::black, 16, 16)});
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Other/littlePacGum.png", '.', ICore::Color::black, ICore::Color::black, 16, 16)});
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Border/doubleAngleBot.png", '#', ICore::Color::black, ICore::Color::black, 16, 16)});
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Border/doubleAngleTop.png", '#', ICore::Color::black, ICore::Color::black, 16, 16)});
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Border/doubleAngleLeft.png", '#', ICore::Color::black, ICore::Color::black, 16, 16)});
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Border/doubleAngleRight.png", '#', ICore::Color::black, ICore::Color::black, 16, 16)});
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Border/oneBotWall.png", '#', ICore::Color::black, ICore::Color::black, 16, 16)});
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Border/oneTopWall.png", '#', ICore::Color::black, ICore::Color::black, 16, 16)});
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Border/oneLeftWall.png", '#', ICore::Color::black, ICore::Color::black, 16, 16)});
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Border/oneRightWall.png", '#', ICore::Color::black, ICore::Color::black, 16, 16)});
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Border/blackWall.png", '#', ICore::Color::black, ICore::Color::black, 16, 16)});
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Border/ballWall.png", '#', ICore::Color::black, ICore::Color::black, 16, 16)});
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Border/door.png", '#', ICore::Color::black, ICore::Color::black, 16, 16)});
    _sprite.push_back({pacman, coreHandle->loadTexture("./Assets/Pacman/Other/pacmanLeft.png", 'C', ICore::Color::yellow, ICore::Color::yellow, 16, 16)});
    _sprite.push_back({ghost1, coreHandle->loadTexture("./Assets/Pacman/Other/pinkBot.png", 'X', ICore::Color::magenta, ICore::Color::magenta, 16, 16)});
    _sprite.push_back({ghost2, coreHandle->loadTexture("./Assets/Pacman/Other/blueBot.png", 'Y', ICore::Color::blue, ICore::Color::blue, 16, 16)});
    _sprite.push_back({ghost3, coreHandle->loadTexture("./Assets/Pacman/Other/redBot.png", 'Z', ICore::Color::red, ICore::Color::red, 16, 16)});
    _sprite.push_back({pacman, coreHandle->loadTexture("./Assets/Pacman/Other/pacmanRight.png", 'C', ICore::Color::yellow, ICore::Color::yellow, 16, 16)});
    _sprite.push_back({pacman, coreHandle->loadTexture("./Assets/Pacman/Other/pacmanTop.png", 'C', ICore::Color::yellow, ICore::Color::yellow, 16, 16)});
    _sprite.push_back({pacman, coreHandle->loadTexture("./Assets/Pacman/Other/pacmanBot.png", 'C', ICore::Color::yellow, ICore::Color::yellow, 16, 16)});
    _sprite.push_back({ghost4, coreHandle->loadTexture("./Assets/Pacman/Other/orangeBot.png", 'A', ICore::Color::white, ICore::Color::white, 16, 16)});
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Other/bigPacGum.png", 'o', ICore::Color::black, ICore::Color::black, 16, 16)});
    // Runner
    _sprite.push_back({ghost1, coreHandle->loadTexture("./Assets/Pacman/Other/runner.png", 'R', ICore::Color::black, ICore::Color::black, 16, 16)});
    _sprite.push_back({ghost2, coreHandle->loadTexture("./Assets/Pacman/Other/runner.png", 'R', ICore::Color::black, ICore::Color::black, 16, 16)});
    _sprite.push_back({ghost3, coreHandle->loadTexture("./Assets/Pacman/Other/runner.png", 'R', ICore::Color::black, ICore::Color::black, 16, 16)});
    _sprite.push_back({ghost4, coreHandle->loadTexture("./Assets/Pacman/Other/runner.png", 'R', ICore::Color::black, ICore::Color::black, 16, 16)});
    //Text to launch game
    _sprite.push_back({mainText, coreHandle->loadTexture("./Assets/Pacman/Font/Univers.ttf", 'P', ICore::Color::white, ICore::Color::white, 16, 16)});
    _sprite.push_back({mainText, coreHandle->loadTexture("./Assets/Pacman/Font/Univers.ttf", 'R', ICore::Color::white, ICore::Color::white, 16, 16)});
    _sprite.push_back({mainText, coreHandle->loadTexture("./Assets/Pacman/Font/Univers.ttf", 'E', ICore::Color::white, ICore::Color::white, 16, 16)});
    _sprite.push_back({mainText, coreHandle->loadTexture("./Assets/Pacman/Font/Univers.ttf", 'S', ICore::Color::white, ICore::Color::white, 16, 16)});
    _sprite.push_back({mainText, coreHandle->loadTexture("./Assets/Pacman/Font/Univers.ttf", 'S', ICore::Color::white, ICore::Color::white, 16, 16)});
    _sprite.push_back({mainText, coreHandle->loadTexture("./Assets/Pacman/Font/Univers.ttf", 'E', ICore::Color::white, ICore::Color::white, 16, 16)});
    _sprite.push_back({mainText, coreHandle->loadTexture("./Assets/Pacman/Font/Univers.ttf", 'N', ICore::Color::white, ICore::Color::white, 16, 16)});
    _sprite.push_back({mainText, coreHandle->loadTexture("./Assets/Pacman/Font/Univers.ttf", 'T', ICore::Color::white, ICore::Color::white, 16, 16)});
    _sprite.push_back({mainText, coreHandle->loadTexture("./Assets/Pacman/Font/Univers.ttf", 'E', ICore::Color::white, ICore::Color::white, 16, 16)});
    _sprite.push_back({mainText, coreHandle->loadTexture("./Assets/Pacman/Font/Univers.ttf", 'R', ICore::Color::white, ICore::Color::white, 16, 16)});

    coreHandle->setFramerate(60);
    coreHandle->setPixelsPerCell(16);
    _core = coreHandle;
}

void Pacman::constructMap()
{
    std::ifstream map("./Maps/pacman_map1.txt", std::ios::in);
    char element;

    if (!map.fail()) {
        while (map.get(element))
            _map.push_back(element);
        std::cout << "map here:" << std::endl;
    } else {
        //error
        std::cout << "fail here:" << std::endl;
    }
}

bool Pacman::movePacman(int i)
{
    int coord = (_sprite[18].pixelPosition.y * 40) + _sprite[18].pixelPosition.x;

    if (_sprite[18].pixelPosition.x == 38 || _sprite[18].pixelPosition.x == 0)
        return (true);
    if (_map[coord + i] == '.' || _map[coord + i] == 'o' || _map[coord + i] == 'X' || _map[coord + i] == 'Y' || _map[coord + i] == 'Z' || _map[coord + i] == 'A' || _map[coord + i] == ' ' ||
        _map[coord + i] == 'C') {
        if (_map[coord + i] == '.') {
            _pacGumEat++;
            _score += 10;
            _map[coord + i] = ' ';
        }
        if (_map[coord + i] == 'o') {
            _score += 100;
            _runner = true;
            _map[coord + i] = ' ';
        }
        return (true);
    }
    return (false);
}

int Pacman::chooseDirection(int pos)
{
    int possibility = 0;
    std::vector<std::string> road;

    if ((_map[pos + 1] == '.' || _map[pos + 1] == 'o' || _map[pos + 1] == 'X' || _map[pos + 1] == 'Y' || _map[pos + 1] == 'Z' || _map[pos + 1] == 'A' || _map[pos + 1] == ' ' ||
        _map[pos + 1] == 'C') && _ghost1Direction != 3) {
        road.push_back("right");
        possibility++;
    }
    if ((_map[pos - 1] == '.' || _map[pos - 1] == 'o' || _map[pos + 2] == 'X' || _map[pos + 2] == 'Y' || _map[pos + 2] == 'Z' || _map[pos + 2] == 'A' || _map[pos + 2] == ' ' ||
        _map[pos - 1] == 'C') && _ghost1Direction != 2) {
        possibility++;
        road.push_back("left");
    }
    if ((_map[pos + 40] == '.' || _map[pos + 40] == 'o' || _map[pos + 40] == 'X' || _map[pos + 40] == 'Y' || _map[pos + 40] == 'Z' || _map[pos + 40] == 'A' || _map[pos + 40] == ' ' ||
        _map[pos + 40] == 'C') && _ghost1Direction != 0) {
        possibility++;
        road.push_back("down");
    }
    if ((_map[pos - 40] == '.' || _map[pos - 40] == 'o' || _map[pos - 40] == 'X' || _map[pos - 40] == 'Y' || _map[pos - 40] == 'Z' || _map[pos - 40] == 'A' || _map[pos - 40] == ' ' ||
        _map[pos - 40] == 'C') && _ghost1Direction != 1) {
        possibility++;
        road.push_back("up");
    }

    if (possibility >= 1) {
        std::string way = road[rand() % road.size()];
        if (way == "up")
            return (0);
        if (way == "down")
            return (1);
        if (way == "right")
            return (2);
        if (way == "left")
            return (3);
    } else if (possibility == 0) {
        if ((_map[pos + 1] == '.' || _map[pos + 1] == 'o' || _map[pos + 1] == 'X' || _map[pos + 1] == 'Y' || _map[pos + 1] == 'Z' || _map[pos + 1] == 'A' || _map[pos + 1] == ' ' ||
            _map[pos + 1] == 'C')) {
            road.push_back("right");
            possibility++;
        }
        if ((_map[pos - 1] == '.' || _map[pos - 1] == 'o' || _map[pos + 2] == 'X' || _map[pos + 2] == 'Y' || _map[pos + 2] == 'Z' || _map[pos + 2] == 'A' || _map[pos + 2] == ' ' ||
            _map[pos - 1] == 'C')) {
            possibility++;
            road.push_back("left");
        }
        if ((_map[pos + 40] == '.' || _map[pos + 40] == 'o' || _map[pos + 40] == 'X' || _map[pos + 40] == 'Y' || _map[pos + 40] == 'Z' || _map[pos + 40] == 'A' || _map[pos + 40] == ' ' ||
            _map[pos + 40] == 'C')) {
            possibility++;
            road.push_back("down");
        }
        if ((_map[pos - 40] == '.' || _map[pos - 40] == 'o' || _map[pos - 40] == 'X' || _map[pos - 40] == 'Y' || _map[pos - 40] == 'Z' || _map[pos - 40] == 'A' || _map[pos - 40] == ' ' ||
            _map[pos - 40] == 'C')) {
            possibility++;
            road.push_back("up");
        }
        if (road.size() > 0) {
            std::string way = road[rand() % road.size()];
            if (way == "up")
                return (0);
            if (way == "down")
                return (1);
            if (way == "right")
                return (2);
            if (way == "left")
                return (3);
        }
    }
    return (-1);
}

bool Pacman::checkWallGhost(int i, int nb)
{
    int coord = (_sprite[nb].pixelPosition.y * 40) + _sprite[nb].pixelPosition.x;

    if (_sprite[nb].pixelPosition.x == 39)
        return (false);
    if (_sprite[nb].pixelPosition.y == 1 && i == (-40))
        return (false);
    if (_map[coord + i] == '.' || _map[coord + i] == 'o' || _map[coord + i] == 'X' || _map[coord + i] == 'Y' || _map[coord + i] == 'Z' || _map[coord + i] == 'A' || _map[coord + i] == ' ' ||
        _map[coord + i] == 'C') {
        return (true);
    }
    return (false);
}

void Pacman::moveGhost()
{
    int coord1 = (_sprite[25].pixelPosition.y * 40) + _sprite[25].pixelPosition.x;
    int coord2 = (_sprite[20].pixelPosition.y * 40) + _sprite[20].pixelPosition.x;
    int coord3 = (_sprite[19].pixelPosition.y * 40) + _sprite[19].pixelPosition.x;
    int coord4 = (_sprite[21].pixelPosition.y * 40) + _sprite[21].pixelPosition.x;
    int tmp = 0;

    if (_ghostFrameRate > 6) {
        if ((tmp = chooseDirection(coord1)) != -1)
            _ghost1Direction = tmp;
        if ((tmp = chooseDirection(coord2)) != -1)
            _ghost2Direction = tmp;
        if ((tmp = chooseDirection(coord3)) != -1)
            _ghost3Direction = tmp;
        if ((tmp = chooseDirection(coord4)) != -1)
            _ghost4Direction = tmp;
        _ghostFrameRate = 0;
        if (_orangeStatus == true) {
            switch(_ghost1Direction) {
                case (int)Direction::left:
                    if (checkWallGhost(-1, 25)) {
                        _sprite[25].pixelPosition.x--;
                        _sprite[30].pixelPosition.x--;
                    }
                    break;
                case (int)Direction::right:
                    if (checkWallGhost(1, 25)) {
                        _sprite[25].pixelPosition.x++;
                        _sprite[30].pixelPosition.x++;
                    }
                    break;
                case (int)Direction::up:
                    if (checkWallGhost(-40, 25)) {
                        _sprite[25].pixelPosition.y--;
                        _sprite[30].pixelPosition.y--;
                    }
                    break;
                case (int)Direction::down:
                    if (checkWallGhost(40, 25)) {
                        _sprite[25].pixelPosition.y++;
                        _sprite[30].pixelPosition.y++;
                    }
                    break;
            }
        }
        if (_blueStatus == true) {
            if (_sprite[20].pixelPosition.x == 19 && _sprite[20].pixelPosition.y == 10) {
                _sprite[20].pixelPosition.x = 19;
                _sprite[20].pixelPosition.y = 8;
                _sprite[28].pixelPosition.x = 19;
                _sprite[28].pixelPosition.y = 8;
            }
            switch(_ghost2Direction) {
                case (int)Direction::left:
                    if (checkWallGhost(-1, 20)) {
                        _sprite[20].pixelPosition.x--;
                        _sprite[28].pixelPosition.x--;
                    }
                    break;
                case (int)Direction::right:
                    if (checkWallGhost(1, 20)) {
                        _sprite[20].pixelPosition.x++;
                        _sprite[28].pixelPosition.x++;
                    }
                    break;
                case (int)Direction::up:
                    if (checkWallGhost(-40, 20)) {
                        _sprite[20].pixelPosition.y--;
                        _sprite[28].pixelPosition.y--;
                    }
                    break;
                case (int)Direction::down:
                    if (checkWallGhost(40, 20)) {
                        _sprite[20].pixelPosition.y++;
                        _sprite[28].pixelPosition.y++;
                    }
                    break;
            }
        }
        if (_pinkStatus == true) {
            if (_sprite[19].pixelPosition.x == 20 && _sprite[19].pixelPosition.y == 10) {
                _sprite[19].pixelPosition.x = 19;
                _sprite[19].pixelPosition.y = 8;
                _sprite[27].pixelPosition.x = 19;
                _sprite[27].pixelPosition.y = 8;
            }
            switch(_ghost3Direction) {
                case (int)Direction::left:
                    if (checkWallGhost(-1, 19)) {
                        _sprite[19].pixelPosition.x--;
                        _sprite[27].pixelPosition.x--;
                    }
                    break;
                case (int)Direction::right:
                    if (checkWallGhost(1, 19)) {
                        _sprite[19].pixelPosition.x++;
                        _sprite[27].pixelPosition.x++;
                    }
                    break;
                case (int)Direction::up:
                    if (checkWallGhost(-40, 19)) {
                        _sprite[19].pixelPosition.y--;
                        _sprite[27].pixelPosition.y--;
                    }
                    break;
                case (int)Direction::down:
                    if (checkWallGhost(40, 19)) {
                        _sprite[19].pixelPosition.y++;
                        _sprite[27].pixelPosition.y++;
                    }
                    break;
            }
        }
        if (_redStatus) {
            if (_sprite[21].pixelPosition.x == 20 && _sprite[21].pixelPosition.y == 10) {
                _sprite[21].pixelPosition.x = 19;
                _sprite[21].pixelPosition.y = 8;
                _sprite[29].pixelPosition.x = 19;
                _sprite[29].pixelPosition.y = 8;
            }
            switch(_ghost4Direction) {
                case (int)Direction::left:
                    if (checkWallGhost(-1, 21)) {
                        _sprite[21].pixelPosition.x--;
                        _sprite[29].pixelPosition.x--;
                    }
                    break;
                case (int)Direction::right:
                    if (checkWallGhost(1, 21)) {
                        _sprite[21].pixelPosition.x++;
                        _sprite[29].pixelPosition.x++;
                    }
                    break;
                case (int)Direction::up:
                    if (checkWallGhost(-40, 21)) {
                        _sprite[21].pixelPosition.y--;
                        _sprite[29].pixelPosition.y--;
                    }
                    break;
                case (int)Direction::down:
                    if (checkWallGhost(40, 21)) {
                        _sprite[21].pixelPosition.y++;
                        _sprite[29].pixelPosition.y++;
                    }
                    break;
            }
        }
    }
    _ghostFrameRate++;
}

void Pacman::updatePosition()
{
    int index = (_sprite[18].pixelPosition.y * 40) + _sprite[18].pixelPosition.x;
    int tmp = 0;
    _frameRate = 0;
    switch(_direction) {
        case (int)Direction::left:
            if (movePacman(-1)) {
                if (_sprite[18].pixelPosition.x == 0) {
                    _sprite[18].pixelPosition.x = 38;
                    _sprite[18].pixelPosition.y = 10;
                    _sprite[22].pixelPosition.x = 38;
                    _sprite[22].pixelPosition.y = 10;
                    _sprite[23].pixelPosition.x = 38;
                    _sprite[23].pixelPosition.y = 10;
                    _sprite[24].pixelPosition.x = 38;
                    _sprite[24].pixelPosition.y = 10;
                    return;
                }
                _sprite[18].pixelPosition.x--;
                _sprite[22].pixelPosition.x--;
                _sprite[23].pixelPosition.x--;
                _sprite[24].pixelPosition.x--;
            }
            break;
        case (int)Direction::right:
            if (movePacman(1)) {
                if (_sprite[18].pixelPosition.x == 38) {
                    tmp = (10 * 40) + 38;
                    if (_map[tmp] == '.') {
                        _pacGumEat++;
                        _map[tmp] = ' ';
                    }
                    _sprite[18].pixelPosition.x = 0;
                    _sprite[18].pixelPosition.y = 10;
                    _sprite[22].pixelPosition.x = 0;
                    _sprite[22].pixelPosition.y = 10;
                    _sprite[23].pixelPosition.x = 0;
                    _sprite[23].pixelPosition.y = 10;
                    _sprite[24].pixelPosition.x = 0;
                    _sprite[24].pixelPosition.y = 10;
                    return;
                }
                _sprite[18].pixelPosition.x++;
                _sprite[22].pixelPosition.x++;
                _sprite[23].pixelPosition.x++;
                _sprite[24].pixelPosition.x++;
            }
            break;
        case (int)Direction::up:
            if (movePacman(-40)) {
                _sprite[18].pixelPosition.y--;
                _sprite[22].pixelPosition.y--;
                _sprite[23].pixelPosition.y--;
                _sprite[24].pixelPosition.y--;
            }
            break;
        case (int)Direction::down:
            if (movePacman(40)) {
                _sprite[18].pixelPosition.y++;
                _sprite[22].pixelPosition.y++;
                _sprite[23].pixelPosition.y++;
                _sprite[24].pixelPosition.y++;
            }
            break;
    }
}

void Pacman::freeGhost()
{
    if (_orangeStatus == false) {
        _orangeStatus = true;
    }
    else if (_blueStatus == false) {
        _blueStatus = true;
    }
    else if (_pinkStatus == false) {
        _pinkStatus = true;
    }
    else if (_redStatus == false) {
        _redStatus = true;
    }
}

bool Pacman::checkCollision()
{
    if ((_sprite[18].pixelPosition.x == _sprite[19].pixelPosition.x && _sprite[18].pixelPosition.y == _sprite[19].pixelPosition.y && _runner == false) ||
        (_sprite[18].pixelPosition.x == _sprite[20].pixelPosition.x && _sprite[18].pixelPosition.y == _sprite[20].pixelPosition.y && _runner == false) ||
        (_sprite[18].pixelPosition.x == _sprite[21].pixelPosition.x && _sprite[18].pixelPosition.y == _sprite[21].pixelPosition.y && _runner == false) ||
        (_sprite[18].pixelPosition.x == _sprite[25].pixelPosition.x && _sprite[18].pixelPosition.y == _sprite[25].pixelPosition.y && _runner == false))
        return (false);
    return (true);
}

void Pacman::restartGame()
{
    //_tmp = 0;
    _frameRate = 0;
    _ghostFrameRate = 0;
    _pacmanHead = 18;
    _pacGumEat = 0;
    _ghost1Direction = 3;
    _ghostOut = 0;
    _timer = 0;
    _direction = 3;
    _map.clear();
    _ghostOutHouse.clear();
    _ghostInHouse.clear();
    _ghostInHouse.push_back("orange");
    _ghostInHouse.push_back("pink");
    _ghostInHouse.push_back("blue");
    _ghostInHouse.push_back("red");
    _status = false;
    _orangeStatus = false;
    _redStatus = false;
    _pinkStatus = false;
    _score = 0;
    _blueStatus = false;
    _runner = false;
    _runnerCounter = 0;
    // Pacman
    _sprite[18].pixelPosition.x = 19;
    _sprite[18].pixelPosition.y = 12;
    _sprite[22].pixelPosition.x = 19;
    _sprite[22].pixelPosition.y = 12;
    _sprite[23].pixelPosition.x = 19;
    _sprite[23].pixelPosition.y = 12;
    _sprite[24].pixelPosition.x = 19;
    _sprite[24].pixelPosition.y = 12;
    // Ghost
    _sprite[19].pixelPosition.x = 20;
    _sprite[19].pixelPosition.y = 10;
    _sprite[27].pixelPosition.x = 20;
    _sprite[27].pixelPosition.y = 10;
    _sprite[20].pixelPosition.x = 19;
    _sprite[20].pixelPosition.y = 10;
    _sprite[28].pixelPosition.x = 19;
    _sprite[28].pixelPosition.y = 10;
    _sprite[21].pixelPosition.x = 18;
    _sprite[21].pixelPosition.y = 10;
    _sprite[29].pixelPosition.x = 18;
    _sprite[29].pixelPosition.y = 10;
    _sprite[25].pixelPosition.x = 19;
    _sprite[25].pixelPosition.y = 8;
    _sprite[30].pixelPosition.x = 19;
    _sprite[30].pixelPosition.y = 8;
    constructMap();
}

void Pacman::eatGhost()
{
    if (_sprite[18].pixelPosition.x == _sprite[27].pixelPosition.x && _sprite[18].pixelPosition.y == _sprite[27].pixelPosition.y &&
        _runner == true) {
        _pinkStatus = false;
        _sprite[27].pixelPosition.x = 20;
        _sprite[27].pixelPosition.y = 10;
        _sprite[19].pixelPosition.x = 20;
        _sprite[19].pixelPosition.y = 10;
        _ghostOut--;
    }
    if (_sprite[18].pixelPosition.x == _sprite[28].pixelPosition.x && _sprite[18].pixelPosition.y == _sprite[28].pixelPosition.y &&
        _runner == true) {
        _blueStatus = false;
        _sprite[28].pixelPosition.x = 19;
        _sprite[28].pixelPosition.y = 10;
        _sprite[20].pixelPosition.x = 19;
        _sprite[20].pixelPosition.y = 10;
        _ghostOut--;
    }
    if (_sprite[18].pixelPosition.x == _sprite[29].pixelPosition.x && _sprite[18].pixelPosition.y == _sprite[29].pixelPosition.y &&
        _runner == true) {
        _redStatus = false;
        _sprite[29].pixelPosition.x = 18;
        _sprite[29].pixelPosition.y = 10;
        _sprite[21].pixelPosition.x = 18;
        _sprite[21].pixelPosition.y = 10;
        _ghostOut--;
    }
    if (_sprite[18].pixelPosition.x == _sprite[30].pixelPosition.x && _sprite[18].pixelPosition.y == _sprite[30].pixelPosition.y &&
        _runner == true) {
        _orangeStatus = false;
        _sprite[30].pixelPosition.x = 19;
        _sprite[30].pixelPosition.y = 8;
        _sprite[25].pixelPosition.x = 19;
        _sprite[25].pixelPosition.y = 8;
        _ghostOut--;
    }
}

void Pacman::update()
{
    //std::cout << _sprite[18].pixelPosition.y << std::endl;
    if (_runner != true && (!checkCollision() && _tmp == 0) || (_core->isButtonPressed(IDisplayModule::Button::F5) && _tmp == 0 && _status == true)) {
        _tmp = 1;
        _status = false;
        restartGame();
    } else if (_core->isButtonPressed(IDisplayModule::Button::Start))
        _status = true;
    if (_status) {
        if (_tmp == 1)
            _tmp = 0;
        if (_pacGumEat != 347) {
            if (_runner == true)
                eatGhost();
            if (_timer > 125 && _ghostOut < 4) {
                _timer = 0;
                _ghostOut++;
                freeGhost();
            }
            if (_runner == true && _runnerCounter > 250) {
                _runnerCounter = 0;
                _runner = false;
            }
            moveGhost();
            if (_frameRate > 3)
                updatePosition();
            _frameRate++;
            if (_core->isButtonPressed(IDisplayModule::Button::Left)) {
                if (movePacman(-1)) {
                    _direction = 3;
                    _pacmanHead = 22;
                }
            }
            if (_core->isButtonPressed(IDisplayModule::Button::Right)) {
                if (movePacman(1)) {
                    _direction = 2;
                    _pacmanHead = 18;
                }
            }
            if (_core->isButtonPressed(IDisplayModule::Button::Up)) {
                if (movePacman(-40)) {
                    _direction = 0;
                    _pacmanHead = 23;
                }
            }
            if (_core->isButtonPressed(IDisplayModule::Button::Down)) {
                if (movePacman(40)) {
                    _direction = 1;
                    _pacmanHead = 24;
                }
            }
            if (_ghostOut < 4)
                _timer++;
            if (_runner == true)
                _runnerCounter++;
        } else {
            restartGame();
        }
    }
}

void Pacman::draw()
{
    _core->clearScreen(ICore::Color::black);
    for (int i = 0, y = 0, z = 0; i < _map.size(); i++, z++) {
        if (_map[i] == '1')
            _core->renderSprite({{(_sprite[2].pixelPosition.x + z) * 16, (_sprite[2].pixelPosition.y + y) * 16}, _sprite[2].texture});
        if (_map[i] == '2')
            _core->renderSprite({{(_sprite[3].pixelPosition.x + z) * 16, (_sprite[3].pixelPosition.y + y) * 16}, _sprite[3].texture});
        if (_map[i] == '3')
            _core->renderSprite({{(_sprite[1].pixelPosition.x + z) * 16, (_sprite[1].pixelPosition.y + y) * 16}, _sprite[1].texture});
        if (_map[i] == '4')
            _core->renderSprite({{(_sprite[0].pixelPosition.x + z) * 16, (_sprite[0].pixelPosition.y + y) * 16}, _sprite[0].texture});
        if (_map[i] == 'r')
            _core->renderSprite({{(_sprite[4].pixelPosition.x + z) * 16, (_sprite[4].pixelPosition.y + y) * 16}, _sprite[4].texture});
        if (_map[i] == 't')
            _core->renderSprite({{(_sprite[5].pixelPosition.x + z) * 16, (_sprite[5].pixelPosition.y + y) * 16}, _sprite[5].texture});
        if (_map[i] == '.')
            _core->renderSprite({{(_sprite[6].pixelPosition.x + z) * 16, (_sprite[6].pixelPosition.y + y) * 16}, _sprite[6].texture});
        if (_map[i] == 'u')
            _core->renderSprite({{(_sprite[7].pixelPosition.x + z) * 16, (_sprite[7].pixelPosition.y + y) * 16}, _sprite[7].texture});
        if (_map[i] == 'h')
            _core->renderSprite({{(_sprite[8].pixelPosition.x + z) * 16, (_sprite[8].pixelPosition.y + y) * 16}, _sprite[8].texture});
        if (_map[i] == 'c')
            _core->renderSprite({{(_sprite[9].pixelPosition.x + z) * 16, (_sprite[9].pixelPosition.y + y) * 16}, _sprite[9].texture});
        if (_map[i] == 'f')
            _core->renderSprite({{(_sprite[10].pixelPosition.x + z) * 16, (_sprite[10].pixelPosition.y + y) * 16}, _sprite[10].texture});
        if (_map[i] == 'g')
            _core->renderSprite({{(_sprite[11].pixelPosition.x + z) * 16, (_sprite[11].pixelPosition.y + y) * 16}, _sprite[11].texture});
        if (_map[i] == 'k')
            _core->renderSprite({{(_sprite[12].pixelPosition.x + z) * 16, (_sprite[12].pixelPosition.y + y) * 16}, _sprite[12].texture});
        if (_map[i] == 'l')
            _core->renderSprite({{(_sprite[13].pixelPosition.x + z) * 16, (_sprite[13].pixelPosition.y + y) * 16}, _sprite[13].texture});
        if (_map[i] == 'm')
            _core->renderSprite({{(_sprite[14].pixelPosition.x + z) * 16, (_sprite[14].pixelPosition.y + y) * 16}, _sprite[14].texture});
        if (_map[i] == 'b')
            _core->renderSprite({{(_sprite[15].pixelPosition.x + z) * 16, (_sprite[15].pixelPosition.y + y) * 16}, _sprite[15].texture});
        if (_map[i] == 'p')
            _core->renderSprite({{(_sprite[16].pixelPosition.x + z) * 16, (_sprite[16].pixelPosition.y + y) * 16}, _sprite[16].texture});
        if (_map[i] == '-')
            _core->renderSprite({{(_sprite[17].pixelPosition.x + z) * 16, (_sprite[17].pixelPosition.y + y) * 16}, _sprite[17].texture});
        if (_map[i] == 'C') {
            switch (_pacmanHead) {
                case 18:
                    _core->renderSprite({{(_sprite[18].pixelPosition.x) * 16, (_sprite[18].pixelPosition.y) * 16}, _sprite[18].texture});
                    break;
                case 22:
                    _core->renderSprite({{(_sprite[22].pixelPosition.x) * 16, (_sprite[22].pixelPosition.y) * 16}, _sprite[22].texture});
                    break;
                case 23:
                    _core->renderSprite({{(_sprite[23].pixelPosition.x) * 16, (_sprite[23].pixelPosition.y) * 16}, _sprite[23].texture});
                    break;
                case 24:
                    _core->renderSprite({{(_sprite[24].pixelPosition.x) * 16, (_sprite[24].pixelPosition.y) * 16}, _sprite[24].texture});
                    break;
            }
        }
        if (_map[i] == 'X') {
            if (_runner == true)
                _core->renderSprite({{(_sprite[27].pixelPosition.x) * 16, (_sprite[27].pixelPosition.y) * 16}, _sprite[27].texture});
            else
                _core->renderSprite({{(_sprite[19].pixelPosition.x) * 16, (_sprite[19].pixelPosition.y) * 16}, _sprite[19].texture});
        }
        if (_map[i] == 'Y') {
            if (_runner == true)
                _core->renderSprite({{(_sprite[28].pixelPosition.x) * 16, (_sprite[28].pixelPosition.y) * 16}, _sprite[28].texture});
            else
                _core->renderSprite({{(_sprite[20].pixelPosition.x) * 16, (_sprite[20].pixelPosition.y) * 16}, _sprite[20].texture});
        }
        if (_map[i] == 'Z') {
            if (_runner == true)
                _core->renderSprite({{(_sprite[29].pixelPosition.x) * 16, (_sprite[29].pixelPosition.y) * 16}, _sprite[29].texture});
            else
                _core->renderSprite({{(_sprite[21].pixelPosition.x) * 16, (_sprite[21].pixelPosition.y) * 16}, _sprite[21].texture});
        }
        if (_map[i] == 'A') {
            if (_runner == true)
                _core->renderSprite({{(_sprite[30].pixelPosition.x) * 16, (_sprite[30].pixelPosition.y) * 16}, _sprite[30].texture});
            else
                _core->renderSprite({{(_sprite[25].pixelPosition.x) * 16, (_sprite[25].pixelPosition.y) * 16}, _sprite[25].texture});
        }
        if (_map[i] == 'o')
            _core->renderSprite({{(_sprite[26].pixelPosition.x + z) * 16, (_sprite[26].pixelPosition.y + y) * 16}, _sprite[26].texture});
        if (_map[i] == '\n') {
            y++;
            z = -1;
        }
    }

    // Text: "Press Enter"
    if (_status == false) {
        _core->renderSprite({{(_sprite[31].pixelPosition.x + 1) * 16, (_sprite[31].pixelPosition.y) * 16}, _sprite[31].texture});
        _core->renderSprite({{(_sprite[32].pixelPosition.x + 2) * 16, (_sprite[32].pixelPosition.y) * 16}, _sprite[32].texture});
        _core->renderSprite({{(_sprite[33].pixelPosition.x + 3) * 16, (_sprite[33].pixelPosition.y) * 16}, _sprite[33].texture});
        _core->renderSprite({{(_sprite[34].pixelPosition.x + 4) * 16, (_sprite[34].pixelPosition.y) * 16}, _sprite[34].texture});
        _core->renderSprite({{(_sprite[35].pixelPosition.x + 5) * 16, (_sprite[35].pixelPosition.y) * 16}, _sprite[35].texture});
        _core->renderSprite({{(_sprite[36].pixelPosition.x + 7) * 16, (_sprite[36].pixelPosition.y) * 16}, _sprite[36].texture});
        _core->renderSprite({{(_sprite[37].pixelPosition.x + 8) * 16, (_sprite[37].pixelPosition.y) * 16}, _sprite[37].texture});
        _core->renderSprite({{(_sprite[38].pixelPosition.x + 9) * 16, (_sprite[38].pixelPosition.y) * 16}, _sprite[38].texture});
        _core->renderSprite({{(_sprite[39].pixelPosition.x + 10) * 16, (_sprite[39].pixelPosition.y) * 16}, _sprite[39].texture});
        _core->renderSprite({{(_sprite[40].pixelPosition.x + 11) * 16, (_sprite[40].pixelPosition.y) * 16}, _sprite[40].texture});
    } else {

    }
    //_core->renderSprite(_sprite[1]);
}

std::unique_ptr<IGameModule> gEpitechArcadeGetGameModuleHandle()
{
    return std::make_unique<Pacman>();
}