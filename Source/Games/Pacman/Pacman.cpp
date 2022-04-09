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
    _ghost1Status = true;
    _ghost2Status = true;
    _ghost3Status = true;
    _score = 0;
    _ghost4Status = true;
    _tmp = 0;
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
    _sprite.push_back({pacman, coreHandle->loadTexture("./Assets/Pacman/Other/pacmanLeft.png", '#', ICore::Color::black, ICore::Color::black, 16, 16)});
    _sprite.push_back({ghost1, coreHandle->loadTexture("./Assets/Pacman/Other/pinkBot.png", '#', ICore::Color::black, ICore::Color::black, 16, 16)});
    _sprite.push_back({ghost2, coreHandle->loadTexture("./Assets/Pacman/Other/blueBot.png", '#', ICore::Color::black, ICore::Color::black, 16, 16)});
    _sprite.push_back({ghost3, coreHandle->loadTexture("./Assets/Pacman/Other/redBot.png", '#', ICore::Color::black, ICore::Color::black, 16, 16)});
    _sprite.push_back({pacman, coreHandle->loadTexture("./Assets/Pacman/Other/pacmanRight.png", '#', ICore::Color::black, ICore::Color::black, 16, 16)});
    _sprite.push_back({pacman, coreHandle->loadTexture("./Assets/Pacman/Other/pacmanTop.png", '#', ICore::Color::black, ICore::Color::black, 16, 16)});
    _sprite.push_back({pacman, coreHandle->loadTexture("./Assets/Pacman/Other/pacmanBot.png", '#', ICore::Color::black, ICore::Color::black, 16, 16)});
    _sprite.push_back({ghost4, coreHandle->loadTexture("./Assets/Pacman/Other/orangeBot.png", '#', ICore::Color::black, ICore::Color::black, 16, 16)});
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Other/bigPacGum.png", '#', ICore::Color::black, ICore::Color::black, 16, 16)});

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

    if (_map[coord + i] == '.' || _map[coord + i] == 'o' || _map[coord + i] == 'X' || _map[coord + i] == 'Y' || _map[coord + i] == 'Z' || _map[coord + i] == 'A' || _map[coord + i] == ' ' ||
        _map[coord + i] == 'C') {
        if (_map[coord + i] == '.') {
            _pacGumEat++;
            _score += 10;
            _map[coord + i] = ' ';
        }
        if (_map[coord + i] == 'o') {
            _score += 100;
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
        if (std::find(_ghostOutHouse.begin(), _ghostOutHouse.end(), "orange") != _ghostOutHouse.end()) {
            switch(_ghost1Direction) {
                case (int)Direction::left:
                    if (checkWallGhost(-1, 25)) {
                        _sprite[25].pixelPosition.x--;
                    }
                    break;
                case (int)Direction::right:
                    if (checkWallGhost(1, 25)) {
                        _sprite[25].pixelPosition.x++;
                    }
                    break;
                case (int)Direction::up:
                    if (checkWallGhost(-40, 25)) {
                        _sprite[25].pixelPosition.y--;
                    }
                    break;
                case (int)Direction::down:
                    if (checkWallGhost(40, 25)) {
                        _sprite[25].pixelPosition.y++;
                    }
                    break;
            }
        }
        if (std::find(_ghostOutHouse.begin(), _ghostOutHouse.end(), "blue") != _ghostOutHouse.end()) {
            if (_sprite[20].pixelPosition.x == 19 && _sprite[20].pixelPosition.y == 10) {
                _sprite[20].pixelPosition.x = 19;
                _sprite[20].pixelPosition.y = 8;
            }
            switch(_ghost1Direction) {
                case (int)Direction::left:
                    if (checkWallGhost(-1, 20)) {
                        _sprite[20].pixelPosition.x--;
                    }
                    break;
                case (int)Direction::right:
                    if (checkWallGhost(1, 20)) {
                        _sprite[20].pixelPosition.x++;
                    }
                    break;
                case (int)Direction::up:
                    if (checkWallGhost(-40, 20)) {
                        _sprite[20].pixelPosition.y--;
                    }
                    break;
                case (int)Direction::down:
                    if (checkWallGhost(40, 20)) {
                        _sprite[20].pixelPosition.y++;
                    }
                    break;
            }
        }
        if (std::find(_ghostOutHouse.begin(), _ghostOutHouse.end(), "pink") != _ghostOutHouse.end()) {
            if (_sprite[19].pixelPosition.x == 18 && _sprite[19].pixelPosition.y == 10) {
                _sprite[19].pixelPosition.x = 19;
                _sprite[19].pixelPosition.y = 8;
            }
            switch(_ghost1Direction) {
                case (int)Direction::left:
                    if (checkWallGhost(-1, 19)) {
                        _sprite[19].pixelPosition.x--;
                    }
                    break;
                case (int)Direction::right:
                    if (checkWallGhost(1, 19)) {
                        _sprite[19].pixelPosition.x++;
                    }
                    break;
                case (int)Direction::up:
                    if (checkWallGhost(-40, 19)) {
                        _sprite[19].pixelPosition.y--;
                    }
                    break;
                case (int)Direction::down:
                    if (checkWallGhost(40, 19)) {
                        _sprite[19].pixelPosition.y++;
                    }
                    break;
            }
        }
        if (std::find(_ghostOutHouse.begin(), _ghostOutHouse.end(), "red") != _ghostOutHouse.end()) {
            if (_sprite[21].pixelPosition.x == 20 && _sprite[21].pixelPosition.y == 10) {
                _sprite[21].pixelPosition.x = 19;
                _sprite[21].pixelPosition.y = 8;
            }
            switch(_ghost1Direction) {
                case (int)Direction::left:
                    if (checkWallGhost(-1, 21)) {
                        _sprite[21].pixelPosition.x--;
                    }
                    break;
                case (int)Direction::right:
                    if (checkWallGhost(1, 21)) {
                        _sprite[21].pixelPosition.x++;
                    }
                    break;
                case (int)Direction::up:
                    if (checkWallGhost(-40, 21)) {
                        _sprite[21].pixelPosition.y--;
                    }
                    break;
                case (int)Direction::down:
                    if (checkWallGhost(40, 21)) {
                        _sprite[21].pixelPosition.y++;
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
    _frameRate = 0;
    switch(_direction) {
        case (int)Direction::left:
            if (movePacman(-1)) {
                if (_map[index - 1] != 'A')
                    _map[index - 1] = 'C';
                _sprite[18].pixelPosition.x--;
                _sprite[22].pixelPosition.x--;
                _sprite[23].pixelPosition.x--;
                _sprite[24].pixelPosition.x--;
            }
            break;
        case (int)Direction::right:
            if (movePacman(1)) {
                if (_map[index + 1] != 'A')
                    _map[index + 1] = 'C';
                _sprite[18].pixelPosition.x++;
                _sprite[22].pixelPosition.x++;
                _sprite[23].pixelPosition.x++;
                _sprite[24].pixelPosition.x++;
            }
            break;
        case (int)Direction::up:
            if (movePacman(-40)) {
                if (_map[index - 40] != 'A')
                    _map[index - 40] = 'C';
                _sprite[18].pixelPosition.y--;
                _sprite[22].pixelPosition.y--;
                _sprite[23].pixelPosition.y--;
                _sprite[24].pixelPosition.y--;
            }
            break;
        case (int)Direction::down:
            if (movePacman(40)) {
                if (_map[index + 40] != 'A')
                    _map[index + 40] = 'C';
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
    if (std::find(_ghostInHouse.begin(), _ghostInHouse.end(), "orange") != _ghostInHouse.end()) {
        std::remove(_ghostInHouse.begin(), _ghostInHouse.end(), "orange");
        _ghostOutHouse.push_back("orange");
    }
    else if (std::find(_ghostInHouse.begin(), _ghostInHouse.end(), "blue") != _ghostInHouse.end()) {
        std::remove(_ghostInHouse.begin(), _ghostInHouse.end(), "blue");
        _ghostOutHouse.push_back("blue");
    }
    else if (std::find(_ghostInHouse.begin(), _ghostInHouse.end(), "pink") != _ghostInHouse.end()) {
        std::remove(_ghostInHouse.begin(), _ghostInHouse.end(), "pink");
        _ghostOutHouse.push_back("pink");
    }
    else if (std::find(_ghostInHouse.begin(), _ghostInHouse.end(), "red") != _ghostInHouse.end()) {
        std::remove(_ghostInHouse.begin(), _ghostInHouse.end(), "red");
        _ghostOutHouse.push_back("red");
    }
}

bool Pacman::checkCollision()
{
    if ((_sprite[18].pixelPosition.x == _sprite[19].pixelPosition.x && _sprite[18].pixelPosition.y == _sprite[19].pixelPosition.y && _ghost1Status == true) ||
        (_sprite[18].pixelPosition.x == _sprite[20].pixelPosition.x && _sprite[18].pixelPosition.y == _sprite[20].pixelPosition.y && _ghost2Status == true) ||
        (_sprite[18].pixelPosition.x == _sprite[21].pixelPosition.x && _sprite[18].pixelPosition.y == _sprite[21].pixelPosition.y && _ghost3Status == true) ||
        (_sprite[18].pixelPosition.x == _sprite[25].pixelPosition.x && _sprite[18].pixelPosition.y == _sprite[25].pixelPosition.y && _ghost4Status == true))
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
    _ghost1Status = true;
    _ghost2Status = true;
    _ghost3Status = true;
    _score = 0;
    _ghost4Status = true;
    _sprite[18].pixelPosition.x = 19;
    _sprite[18].pixelPosition.y = 12;
    _sprite[22].pixelPosition.x = 19;
    _sprite[22].pixelPosition.y = 12;
    _sprite[23].pixelPosition.x = 19;
    _sprite[23].pixelPosition.y = 12;
    _sprite[24].pixelPosition.x = 19;
    _sprite[24].pixelPosition.y = 12;

    _sprite[19].pixelPosition.x = 20;
    _sprite[19].pixelPosition.y = 10;
    _sprite[20].pixelPosition.x = 19;
    _sprite[20].pixelPosition.y = 10;
    _sprite[21].pixelPosition.x = 18;
    _sprite[21].pixelPosition.y = 10;
    _sprite[25].pixelPosition.x = 19;
    _sprite[25].pixelPosition.y = 8;
    constructMap();
}

void Pacman::update()
{
    if (!checkCollision() && _tmp == 0) {
        _tmp = 1;
        _status = false;
        restartGame();
    }
    if (_core->isButtonPressed(IDisplayModule::Button::Start))
        _status = true;
    if (_status) {
        if (_tmp == 1)
            _tmp = 0;
        if (_pacGumEat != 346) {
            if (_timer > 125 && _ghostOut < 4) {
                _timer = 0;
                _ghostOut++;
                freeGhost();
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
            _timer++;
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
        if (_map[i] == 'X')
            _core->renderSprite({{(_sprite[19].pixelPosition.x) * 16, (_sprite[19].pixelPosition.y) * 16}, _sprite[19].texture});
        if (_map[i] == 'Y')
            _core->renderSprite({{(_sprite[20].pixelPosition.x) * 16, (_sprite[20].pixelPosition.y) * 16}, _sprite[20].texture});
        if (_map[i] == 'Z')
            _core->renderSprite({{(_sprite[21].pixelPosition.x) * 16, (_sprite[21].pixelPosition.y) * 16}, _sprite[21].texture});
        if (_map[i] == 'A')
            _core->renderSprite({{(_sprite[25].pixelPosition.x) * 16, (_sprite[25].pixelPosition.y) * 16}, _sprite[25].texture});
        if (_map[i] == 'o')
            _core->renderSprite({{(_sprite[26].pixelPosition.x + z) * 16, (_sprite[26].pixelPosition.y + y) * 16}, _sprite[26].texture});
        if (_map[i] == '\n') {
            y++;
            z = -1;
        }
    }
    //_core->renderSprite(_sprite[1]);
}

std::unique_ptr<IGameModule> gEpitechArcadeGetGameModuleHandle()
{
    return std::make_unique<Pacman>();
}