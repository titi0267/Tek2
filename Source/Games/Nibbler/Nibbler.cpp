/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-alexandre.frantz
** File description:
** Nibbler
*/

#include "Nibbler.hpp"

Nibbler::Nibbler()
{
    _gum = true;
    constructMap();
    _frameRate = 1;
    _counter = 0;
    _frameKey = 1;
    _frameNext = 1;
    _pixelPerCell = 16;
    _end = true;
    tailStop = 2;
}

Nibbler::~Nibbler()
{
}

void Nibbler::init(ICore *coreHandle)
{
    ICore::Vector2u windowSize{20 * (uint32_t)_pixelPerCell, 11 * (uint32_t)_pixelPerCell};
    ICore::Vector2u border{0, 0};
    ICore::Vector2u grass{0, 0};
    ICore::Vector2u gums{9 * (uint32_t)_pixelPerCell, 3 * (uint32_t)_pixelPerCell};
    ICore::Vector2u head{10 * (uint32_t)_pixelPerCell, 5 * (uint32_t)_pixelPerCell};
    ICore::Vector2u body{9 * (uint32_t)_pixelPerCell, 5 * (uint32_t)_pixelPerCell};
    ICore::Vector2u tail{7 * (uint32_t)_pixelPerCell, 5 * (uint32_t)_pixelPerCell};

    coreHandle->openWindow(windowSize);
    _sprite.push_back({{grass, coreHandle->loadTexture("./Assets/Nibbler/Grass.png", ' ', ICore::Color::black, ICore::Color::black, 16, 16)}, {grass, coreHandle->loadTexture("./Assets/Nibbler/Grass.png", ' ', ICore::Color::black, ICore::Color::black, 16, 16)}, (int)Direction::up, (int)Direction::up, false, 0, false});
    _sprite.push_back({{gums, coreHandle->loadTexture("./Assets/Nibbler/Gums.png", 'O', ICore::Color::red, ICore::Color::black, 16, 16)}, {gums, coreHandle->loadTexture("./Assets/Nibbler/Gums.png", 'O', ICore::Color::red, ICore::Color::black, 16, 16)}, (int)Direction::up, (int)Direction::up, false, 1, false});
    _sprite.push_back({{border, coreHandle->loadTexture("./Assets/Nibbler/Border.png", '#', ICore::Color::black, ICore::Color::black, 16, 16)}, {border, coreHandle->loadTexture("./Assets/Nibbler/Border.png", '#', ICore::Color::black, ICore::Color::black, 16, 16)}, (int)Direction::up,(int)Direction::up, false, 2, false});
    _sprite.push_back({{head, coreHandle->loadTexture("./Assets/Nibbler/HeadUp.png", ' ', ICore::Color::red, ICore::Color::red, 16, 16)}, {head, coreHandle->loadTexture("./Assets/Nibbler/HeadUp.png", ' ', ICore::Color::red, ICore::Color::red, 16, 16)}, (int)Direction::up,(int)Direction::up, false, 3, false});
    _sprite.push_back({{head, coreHandle->loadTexture("./Assets/Nibbler/HeadDown.png", ' ', ICore::Color::red, ICore::Color::red, 16, 16)}, {head, coreHandle->loadTexture("./Assets/Nibbler/HeadDown.png", ' ', ICore::Color::red, ICore::Color::red, 16, 16)}, (int)Direction::down,(int)Direction::down, false, 4, false});
    _sprite.push_back({{head, coreHandle->loadTexture("./Assets/Nibbler/HeadRight.png", ' ', ICore::Color::red, ICore::Color::red, 16, 16)}, {head, coreHandle->loadTexture("./Assets/Nibbler/HeadRight.png", ' ', ICore::Color::red, ICore::Color::red, 16, 16)}, (int)Direction::right,(int)Direction::right, false, 5, false});
    _sprite.push_back({{head, coreHandle->loadTexture("./Assets/Nibbler/HeadLeft.png", ' ', ICore::Color::red, ICore::Color::red, 16, 16)}, {head, coreHandle->loadTexture("./Assets/Nibbler/HeadLeft.png", ' ', ICore::Color::red, ICore::Color::red, 16, 16)}, (int)Direction::left, (int)Direction::left, false, 6, false});
    /*up*/_sprite.push_back({{body, coreHandle->loadTexture("./Assets/Nibbler/BodyVertical.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, {body, coreHandle->loadTexture("./Assets/Nibbler/BodyVertical.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, (int)Direction::up, (int)Direction::up, false, 7, false});
    /*down*/_sprite.push_back({{body, coreHandle->loadTexture("./Assets/Nibbler/BodyVertical.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, {body, coreHandle->loadTexture("./Assets/Nibbler/BodyVertical.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, (int)Direction::down, (int)Direction::down, false, 8, false});
    /*right*/_sprite.push_back({{body, coreHandle->loadTexture("./Assets/Nibbler/BodyHorizontal.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, {body, coreHandle->loadTexture("./Assets/Nibbler/BodyHorizontal.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, (int)Direction::right,(int)Direction::right, false, 9, false});
    /*left*/_sprite.push_back({{body, coreHandle->loadTexture("./Assets/Nibbler/BodyHorizontal.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, {body, coreHandle->loadTexture("./Assets/Nibbler/BodyHorizontal.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, (int)Direction::left,(int)Direction::left, false, 10, false});
    /*rightup11*/_sprite.push_back({{body, coreHandle->loadTexture("./Assets/Nibbler/BodyCornerLeftUp.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, {body, coreHandle->loadTexture("./Assets/Nibbler/BodyCornerLeftUp.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, (int)Direction::right,(int)Direction::up, false, 11, false});
    /*downleft12*/_sprite.push_back({{body, coreHandle->loadTexture("./Assets/Nibbler/BodyCornerLeftUp.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, {body, coreHandle->loadTexture("./Assets/Nibbler/BodyCornerLeftUp.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, (int)Direction::down,(int)Direction::left, false, 12, false});
    /*leftup13*/_sprite.push_back({{body, coreHandle->loadTexture("./Assets/Nibbler/BodyCornerRightUp.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, {body, coreHandle->loadTexture("./Assets/Nibbler/BodyCornerRightUp.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, (int)Direction::left, (int)Direction::up, false, 13, false});
    /*downright14*/_sprite.push_back({{body, coreHandle->loadTexture("./Assets/Nibbler/BodyCornerRightUp.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, {body, coreHandle->loadTexture("./Assets/Nibbler/BodyCornerRightUp.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, (int)Direction::down, (int)Direction::right, false, 14, false});
    /*upleft15*/_sprite.push_back({{body, coreHandle->loadTexture("./Assets/Nibbler/BodyCornerLeftDown.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, {body, coreHandle->loadTexture("./Assets/Nibbler/BodyCornerLeftDown.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, (int)Direction::up,(int)Direction::left, false, 15, false});
    /*rightdown16*/_sprite.push_back({{body, coreHandle->loadTexture("./Assets/Nibbler/BodyCornerLeftDown.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, {body, coreHandle->loadTexture("./Assets/Nibbler/BodyCornerLeftDown.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, (int)Direction::right,(int)Direction::down, false, 16, false});
    /*upright17*/_sprite.push_back({{body, coreHandle->loadTexture("./Assets/Nibbler/BodyCornerRightDown.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, {body, coreHandle->loadTexture("./Assets/Nibbler/BodyCornerRightDown.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, (int)Direction::up,(int)Direction::right ,false, 17, false});
    /*leftdown18*/_sprite.push_back({{body, coreHandle->loadTexture("./Assets/Nibbler/BodyCornerRightDown.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, {body, coreHandle->loadTexture("./Assets/Nibbler/BodyCornerRightDown.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, (int)Direction::left,(int)Direction::down ,false, 18, false});
    _sprite.push_back({{tail, coreHandle->loadTexture("./Assets/Nibbler/TailUp.png", ' ', ICore::Color::cyan, ICore::Color::cyan, 16, 16)}, {tail, coreHandle->loadTexture("./Assets/Nibbler/TailUp.png", ' ', ICore::Color::cyan, ICore::Color::cyan, 16, 16)}, (int)Direction::up,(int)Direction::up, true, 19, false});
    _sprite.push_back({{tail, coreHandle->loadTexture("./Assets/Nibbler/TailDown.png", ' ', ICore::Color::cyan, ICore::Color::cyan, 16, 16)}, {tail, coreHandle->loadTexture("./Assets/Nibbler/TailDown.png", ' ', ICore::Color::cyan, ICore::Color::cyan, 16, 16)}, (int)Direction::down,(int)Direction::down, true, 20, false});
    _sprite.push_back({{tail, coreHandle->loadTexture("./Assets/Nibbler/TailLeft.png", ' ', ICore::Color::cyan, ICore::Color::cyan, 16, 16)}, {tail, coreHandle->loadTexture("./Assets/Nibbler/TailLeft.png", ' ', ICore::Color::cyan, ICore::Color::cyan, 16, 16)}, (int)Direction::left,(int)Direction::left, true, 21, false});
    _sprite.push_back({{tail, coreHandle->loadTexture("./Assets/Nibbler/TailRight.png", ' ', ICore::Color::cyan, ICore::Color::cyan, 16, 16)}, {tail, coreHandle->loadTexture("./Assets/Nibbler/TailRight.png", ' ', ICore::Color::cyan, ICore::Color::cyan, 16, 16)}, (int)Direction::right,(int)Direction::right, true, 22, false});
    constructSnake();
    coreHandle->setFramerate(30);
    coreHandle->setPixelsPerCell(16);
    _core = coreHandle;
}

void Nibbler::constructMap()
{
    std::ifstream map("./Maps/nibbler_map.txt", std::ios::in);
    char element;

    if (!map.fail()) {
        while (map.get(element))
            _map.push_back(element);
    } else {
        //error
    }
}

void Nibbler::constructSnake()
{
    ICore::Vector2u bodyPos{_sprite[9]._sprt.pixelPosition.x - _pixelPerCell, _sprite[9]._sprt.pixelPosition.y};

    _sprite[1]._sprt.pixelPosition.x = 9 * _pixelPerCell;
    _sprite[1]._sprt.pixelPosition.y = 3 * _pixelPerCell;
    _snake.push_back({{_sprite[5]._sprt.pixelPosition , _sprite[5]._sprt.texture}, {_sprite[5]._sprt.pixelPosition , _sprite[5]._sprt.texture}, _sprite[5]._direction, _sprite[5]._direction, false, 5, false});
    _snake.push_back({{_sprite[9]._sprt.pixelPosition, _sprite[9]._sprt.texture}, {_sprite[9]._sprt.pixelPosition, _sprite[9]._sprt.texture}, _sprite[9]._direction,_sprite[9]._direction, false, 9, false});
    _snake.push_back({{bodyPos, _sprite[9]._sprt.texture}, {bodyPos, _sprite[9]._sprt.texture}, _sprite[9]._direction,_sprite[9]._direction, false, 9, false});
    _snake.push_back({{_sprite[22]._sprt.pixelPosition, _sprite[22]._sprt.texture}, {_sprite[22]._sprt.pixelPosition, _sprite[22]._sprt.texture}, _sprite[22]._direction,_sprite[22]._direction, true, 22, false});
}

/*   check all snake's position compared with gum position in X   */
bool Nibbler::checkSnakePosX(unsigned random)
{
    for (int d = 0; d < _snake.size(); d++) {
        if (_snake[d]._sprt.pixelPosition.x == random) //pas les bonnes sprites
            return true;
    }
    return false;
}

/*   check all snake's position compared with gum position in Y  */
bool Nibbler::checkSnakePosY(unsigned random)
{
    for (int d = 0; d < _snake.size(); d++) {
        if (_snake[d]._sprt.pixelPosition.y == random) //pas les bonnes sprites ?
            return true;
    }
    return false;
}

/*   check snake's head position compared with gum position in X  */
bool Nibbler::checkSnakeHeadPosX(unsigned random)
{
    if (_snake[0]._sprt.pixelPosition.x == random)
        return true;
    return false;
}

/*   check snake's head position compared with gum position in Y  */
bool Nibbler::checkSnakeHeadPosY(unsigned random)
{
    if (_snake[0]._sprt.pixelPosition.y == random)
        return true;
    return false;
}

/*  Add new body section when gum position matches with snake's head position  */
void Nibbler::gumEated()
{
    auto itr = _snake.end() - 1;
    int size = _snake.size() - 2;
    auto last = _snake[_snake.size()-1];

    _snake.insert(itr, {{_snake[size]._sprt.pixelPosition, _snake[size]._sprt.texture}, {_snake[size]._nextSprt.pixelPosition, _snake[size]._nextSprt.texture}, _snake[size]._direction, _snake[size]._nextDirection, _snake[size].isTail, _snake[size].index, _snake[size].newly});
    size = _snake.size() - 2;
    _snake[size].newly = true;
    tailStop = 0;
    _addNewBody = true;
    _gum = false;
}

/*******************************************************/
/*                                                     */
/*   Check if Gum is on the map:                       */
/*        - if it is check if snakes head is on it     */
/*        - if it isn't find new free position on map  */
/*                                                     */
/*******************************************************/
void Nibbler::setGum()
{
    /*int randomX;
    int randomY;
*/
    if (_gum == true) {
        if (checkSnakeHeadPosX(_sprite[1]._sprt.pixelPosition.x) == true && checkSnakeHeadPosY(_sprite[1]._sprt.pixelPosition.y) == true)
            gumEated();
    }
    /*if (_gum == false) {
        randomX = rand() % 19 + 1;
        randomY = rand() % 10 + 1;
        while (1) {
            if (checkSnakePosX(randomX) == false && checkSnakePosY(randomY) == false)// && (randomY != 0 && randomY != 10) && (randomX != 0 && randomX != 20))
                break;
            randomX = rand() % 19 + 1;
            randomY = rand() % 10 + 1;
        }
        _sprite[1]._sprt.pixelPosition.x = randomX;
        _sprite[1]._sprt.pixelPosition.y = randomY;
        _gum == true;
    }*/
}

void Nibbler::collisionHimself()
{
    for (int i = 1; i < _snake.size(); i++) {
        if (_snake[0]._sprt.pixelPosition.x == _snake[i]._sprt.pixelPosition.x && _snake[0]._sprt.pixelPosition.y == _snake[i]._sprt.pixelPosition.y) {
            _end = true;
            for (int d = 0; _snake.size() != 0; d++) {
                _snake.pop_back();
            }
            constructSnake();
            break;
        }
    }
}

void Nibbler::collisionWall(int x, int y)
{
    if (x == _snake[0]._sprt.pixelPosition.x && y == _snake[0]._sprt.pixelPosition.y) {
        _end = true;
        for (int d = 0; _snake.size() != 0; d++) {
            _snake.pop_back();
        }
        constructSnake();
    }
}


/**************************************/
/*                                    */
/*   Separate move functions for      */
/*         head, body & tail          */
/*                                    */
/**************************************/

void Nibbler::headMoves()
{
    switch (_snake[0]._direction)
    {
    case (int)Direction::up:
        _snake[0]._sprt.texture = _sprite[3]._sprt.texture;
        _snake[0]._direction = (int)Direction::up;
        break;
    case (int)Direction::down:
        _snake[0]._sprt.texture = _sprite[4]._sprt.texture;
        _snake[0]._direction = (int)Direction::down;
        break;
    case (int)Direction::right:
        _snake[0]._sprt.texture = _sprite[5]._sprt.texture;
        _snake[0]._direction = (int)Direction::right;
        break;
    case (int)Direction::left:
        _snake[0]._sprt.texture = _sprite[6]._sprt.texture;
        _snake[0]._direction = (int)Direction::left;
        break;
    default:
        break;
    }

    switch (_snake[0]._nextDirection)
    {
    case (int)Direction::up:
        _snake[0]._nextSprt.pixelPosition.y -= _pixelPerCell;
        _snake[0]._nextSprt.texture = _sprite[3]._sprt.texture;
        break;
    case (int)Direction::down:
        _snake[0]._nextSprt.pixelPosition.y += _pixelPerCell;
        _snake[0]._nextSprt.texture = _sprite[4]._sprt.texture;
        break;
    case (int)Direction::right:
        _snake[0]._nextSprt.pixelPosition.x += _pixelPerCell;
        _snake[0]._nextSprt.texture = _sprite[5]._sprt.texture;
        break;
    case (int)Direction::left:
        _snake[0]._nextSprt.pixelPosition.x -= _pixelPerCell;
        _snake[0]._nextSprt.texture = _sprite[6]._sprt.texture;
        break;
    default:
        break;
    }
    _frameRate = 1;
}

void Nibbler::tailMoves()
{
    int i = _snake.size() - 1;

    if (_snake[i - 1].newly == true)
        return;
    switch(_snake[i - 1]._direction)
    {
        case (int)Direction::up:
            _snake[i]._nextSprt.texture = _sprite[19]._sprt.texture;
            _snake[i]._nextDirection = (int)Direction::up;
            break;
        case (int)Direction::down:
            _snake[i]._nextSprt.texture = _sprite[20]._sprt.texture;
            _snake[i]._nextDirection = (int)Direction::down;
            break;
        case (int)Direction::left:
            _snake[i]._nextSprt.texture = _sprite[21]._sprt.texture;
            _snake[i]._nextDirection = (int)Direction::left;
            break;
        case (int)Direction::right:
            _snake[i]._nextSprt.texture = _sprite[22]._sprt.texture;
            _snake[i]._nextDirection = (int)Direction::right;
            break;
        default:
            break;
    }
    switch (_snake[i]._direction)
    {
    case (int)Direction::up:
        _snake[i]._nextSprt.pixelPosition.y -= _pixelPerCell;
        _snake[i]._nextSprt.texture = _sprite[19]._sprt.texture;
        chooseTailRotation(i);
        break;
    case (int)Direction::down:
        _snake[i]._nextSprt.pixelPosition.y += _pixelPerCell;
        _snake[i]._nextSprt.texture = _sprite[20]._sprt.texture;
        chooseTailRotation(i);
        break;
    case (int)Direction::left:
        _snake[i]._nextSprt.pixelPosition.x -= _pixelPerCell;
        _snake[i]._nextSprt.texture = _sprite[21]._sprt.texture;
        chooseTailRotation(i);
        break;
    case (int)Direction::right:
        _snake[i]._nextSprt.pixelPosition.x += _pixelPerCell;
        _snake[i]._nextSprt.texture = _sprite[22]._sprt.texture;
        chooseTailRotation(i);
        break;
    default:
        break;
    }
}

void Nibbler::bodyMoves(int i)
{
    if (_snake[i].newly == true)
        return;
    _snake[i]._nextDirection = _snake[i - 1]._nextDirection;
    switch (_snake[i]._direction)
    {
    case (int)Direction::up:
        _snake[i]._nextSprt.pixelPosition.y -= _pixelPerCell;
        chooseCorner(i);
        break;
    case (int)Direction::down:
        _snake[i]._nextSprt.pixelPosition.y += _pixelPerCell;
        chooseCorner(i);
        break;
    case (int)Direction::left:
        _snake[i]._nextSprt.pixelPosition.x -= _pixelPerCell;
        chooseCorner(i);
        break;
    case (int)Direction::right:
        _snake[i]._nextSprt.pixelPosition.x += _pixelPerCell;
        chooseCorner(i);
        break;
    }
}

void Nibbler::handleNew()
{
    for (int i = 0; i < _snake.size(); i++) {
        if (_snake[i].newly == true)
            _snake[i].newly = false;
    }
}

void Nibbler::chooseCorner(int i)
{
    switch (_snake[i]._direction) {
        case (int)Direction::up:
            if (_snake[i]._nextDirection == (int)Direction::right)
                rightCorner(i);
            else if (_snake[i]._nextDirection == (int)Direction::left) {
                leftCorner(i);
            } else {
                if (_snake[i].isTail == false) {
                    _snake[i]._nextSprt.texture = _sprite[7]._sprt.texture;
                    _snake[i]._nextDirection = _sprite[7]._nextDirection;
                }
            }
            break;
        case (int)Direction::down:
            if (_snake[i]._nextDirection == (int)Direction::right)
                rightCorner(i);
            else if (_snake[i]._nextDirection == (int)Direction::left) {
                leftCorner(i);
            } else {
                if (_snake[i].isTail == false) {
                    _snake[i]._nextSprt.texture = _sprite[8]._sprt.texture;
                    _snake[i]._nextDirection = _sprite[8]._nextDirection;
                }
            }
            break;
        case (int)Direction::left:
            if (_snake[i]._nextDirection == (int)Direction::up) {
                upCorner(i);
            } else if (_snake[i]._nextDirection == (int)Direction::down) {
                downCorner(i);
            } else {
                if (_snake[i].isTail == false) {
                    _snake[i]._nextSprt.texture = _sprite[10]._sprt.texture;
                    _snake[i]._nextDirection = _sprite[10]._nextDirection;
                }
            }
            break;
        case (int)Direction::right:
            if (_snake[i]._nextDirection == (int)Direction::up) {
                upCorner(i);
            } else if (_snake[i]._nextDirection == (int)Direction::down) {
                downCorner(i);
            } else {
                if (_snake[i].isTail == false) {
                    _snake[i]._nextSprt.texture = _sprite[9]._sprt.texture;
                    _snake[i]._nextDirection = _sprite[9]._nextDirection;
                }
            }
            break;
    }
}

void Nibbler::chooseTailRotation(int i)
{
    if (_snake[i].isTail == true) {
        switch (_snake[i]._direction)
        {
        case (int)Direction::up:
            if (_snake[i]._nextDirection == (int)Direction::down) {
                _snake[i]._nextDirection = _snake[i - 1]._direction;
                _snake[i]._nextSprt.texture = _sprite[20]._sprt.texture;
            } else if (_snake[i]._nextDirection == (int)Direction::right) {
                _snake[i]._nextDirection = _snake[i - 1]._direction;
                _snake[i]._nextSprt.texture = _sprite[22]._sprt.texture;
            } else if (_snake[i]._nextDirection == (int)Direction::left) {
                _snake[i]._nextDirection = _snake[i - 1]._direction;
                _snake[i]._nextSprt.texture = _sprite[21]._sprt.texture;
            } else {
                _snake[i]._nextDirection = _snake[i - 1]._direction;
                _snake[i]._nextSprt.texture = _sprite[19]._sprt.texture;
            }
            break;
        case (int)Direction::down:
            if (_snake[i]._nextDirection == (int)Direction::up) {
                _snake[i]._nextDirection = _snake[i - 1]._direction;
                _snake[i]._nextSprt.texture = _sprite[19]._sprt.texture;
            } else if (_snake[i]._nextDirection == (int)Direction::right) {
                _snake[i]._nextDirection = _snake[i - 1]._direction;
                _snake[i]._nextSprt.texture = _sprite[22]._sprt.texture;
            } else if (_snake[i]._nextDirection == (int)Direction::left) {
                _snake[i]._nextDirection = _snake[i - 1]._direction;
                _snake[i]._nextSprt.texture = _sprite[21]._sprt.texture;
            } else {
                _snake[i]._nextDirection = _snake[i - 1]._direction;
                _snake[i]._nextSprt.texture = _sprite[20]._sprt.texture;
            }
            break;
        case (int)Direction::right:
            if (_snake[i]._nextDirection == (int)Direction::down) {
                _snake[i]._nextDirection = _snake[i - 1]._direction;
                _snake[i]._nextSprt.texture = _sprite[20]._sprt.texture;
            } else if (_snake[i]._nextDirection == (int)Direction::up) {
                _snake[i]._nextDirection = _snake[i - 1]._direction;
                _snake[i]._nextSprt.texture = _sprite[19]._sprt.texture;
            } else if (_snake[i]._nextDirection == (int)Direction::left) {
                _snake[i]._nextDirection = _snake[i - 1]._direction;
                _snake[i]._nextSprt.texture = _sprite[21]._sprt.texture;
            } else {
                _snake[i]._nextDirection = _snake[i - 1]._direction;
                _snake[i]._nextSprt.texture = _sprite[22]._sprt.texture;
            }
            break;
        case (int)Direction::left:
            if (_snake[i]._nextDirection == (int)Direction::down) {
                _snake[i]._nextDirection = _snake[i - 1]._direction;
                _snake[i]._nextSprt.texture = _sprite[20]._sprt.texture;
            } else if (_snake[i]._nextDirection == (int)Direction::right) {
                _snake[i]._nextDirection = _snake[i - 1]._direction;
                _snake[i]._nextSprt.texture = _sprite[22]._sprt.texture;
            } else if (_snake[i]._nextDirection == (int)Direction::up) {
                _snake[i]._nextDirection = _snake[i - 1]._direction;
                _snake[i]._nextSprt.texture = _sprite[19]._sprt.texture;
            } else {
                _snake[i]._nextDirection = _snake[i - 1]._direction;
                _snake[i]._nextSprt.texture = _sprite[21]._sprt.texture;
            }
            break;
        }
    }
}

void Nibbler::downCorner(int i)
{
    switch (_snake[i]._direction)
    {
    case (int)Direction::right:
        if (_snake[i - 1]._nextDirection == (int)Direction::down)
            _snake[i]._nextSprt.texture = _sprite[16]._sprt.texture;
            _snake[i]._nextDirection = _sprite[16]._nextDirection;
        break;
    case (int)Direction::left:
        if (_snake[i - 1]._nextDirection == (int)Direction::down)
            _snake[i]._nextSprt.texture = _sprite[18]._sprt.texture;
            _snake[i]._nextDirection = _sprite[18]._nextDirection;
        break;
    }
}

void Nibbler::upCorner(int i)
{
    switch (_snake[i]._direction)
    {
        case (int)Direction::right:
            if (_snake[i - 1]._nextDirection == (int)Direction::up) {
                _snake[i]._nextSprt.texture = _sprite[11]._sprt.texture;
                _snake[i]._nextDirection = _sprite[11]._nextDirection;
            }
        break;
        case (int)Direction::left:
            if (_snake[i - 1]._nextDirection == (int)Direction::up) {
                if (_snake[i].isTail == false) {
                    _snake[i]._nextSprt.texture = _sprite[13]._sprt.texture;
                    _snake[i]._nextDirection = _sprite[13]._nextDirection;
                } else {
                    _snake[i]._nextSprt.texture = _sprite[18]._sprt.texture;
                    _snake[i]._nextDirection = (int)Direction::up;
                }
            }
        break;
    }
}

void Nibbler::rightCorner(int i)
{
    switch (_snake[i]._direction)
    {
    case (int)Direction::up:
        if (_snake[i - 1]._nextDirection == (int)Direction::right) {
            if (_snake[i].isTail == false) {
                _snake[i]._nextSprt.texture = _sprite[17]._sprt.texture;
                _snake[i]._nextDirection = _sprite[17]._nextDirection;
            } else {
                _snake[i]._nextSprt.texture = _sprite[24]._sprt.texture;
                _snake[i]._nextDirection = (int)Direction::right;
            }
        }
        else if (_snake[i - 1]._nextDirection == (int)Direction::left) {
            if (_snake[i].isTail == false) {
                _snake[i]._nextSprt.texture = _sprite[13]._sprt.texture;
                _snake[i]._nextDirection = _sprite[13]._nextDirection;
            } else {
                _snake[i]._nextSprt.texture = _sprite[22]._sprt.texture;
                _snake[i]._nextDirection = (int)Direction::left;
            }
        }
        break;
    case (int)Direction::down:
        if (_snake[i - 1]._nextDirection == (int)Direction::right) {
            if (_snake[i].isTail == false) {
                _snake[i]._nextSprt.texture = _sprite[14]._sprt.texture;
                _snake[i]._nextDirection = _sprite[14]._nextDirection;
            } else {
                _snake[i]._nextSprt.texture = _sprite[25]._sprt.texture;
                _snake[i]._nextDirection = (int)Direction::right;
            }
        }
    }
}

void Nibbler::leftCorner(int i)
{
    switch (_snake[i]._direction)
    {
    case (int)Direction::up:
        if (_snake[i - 1]._nextDirection == (int)Direction::left) {
            _snake[i]._nextSprt.texture = _sprite[15]._sprt.texture;
            _snake[i]._nextDirection = _sprite[15]._nextDirection;
        }
        break;
    case (int)Direction::down:
        if (_snake[i - 1]._nextDirection == (int)Direction::left) {
            _snake[i]._nextSprt.texture = _sprite[12]._sprt.texture;
            _snake[i]._nextDirection = _sprite[12]._nextDirection;
        }
        break;
    }
}

void Nibbler::draw()
{
        _core->clearScreen(ICore::Color::black);
        for (int i = 0, y = 0, z = 0; i < _map.size(); i++, z++) {
            if (_map[i] == '#') {
                _core->renderSprite({{_sprite[2]._sprt.pixelPosition.x + (z * _pixelPerCell), _sprite[2]._sprt.pixelPosition.y + (y * _pixelPerCell)}, _sprite[2]._sprt.texture});
                if (_end == false)
                    collisionWall(_sprite[2]._sprt.pixelPosition.x + (z * _pixelPerCell), _sprite[2]._sprt.pixelPosition.y + (y * _pixelPerCell));
            }
            if (_map[i] == ' ')
                _core->renderSprite({{_sprite[0]._sprt.pixelPosition.x + (z * _pixelPerCell), _sprite[0]._sprt.pixelPosition.y + (y * _pixelPerCell)}, _sprite[0]._sprt.texture});
            if (_map[i] == '\n') {
                y++;
                z = -1;
            }
        }
        _core->renderSprite(_sprite[1]._sprt);
        for (int i = _snake.size() - 1; i != -1; i--) {
            _core->renderSprite(_snake[i]._sprt);
            _snake[i]._sprt.pixelPosition = _snake[i]._nextSprt.pixelPosition;
        }
        if (_frameNext > 7 && _end == false) {
            for (int i = _snake.size() - 1; i != -1; i--) {
                _snake[i]._sprt = _snake[i]._nextSprt;
                _snake[i]._direction = _snake[i]._nextDirection;
            }
            _frameNext = 1;
        }
        _frameNext++;
}

void Nibbler::update()
{
    if (_core->isButtonPressed(IDisplayModule::Button::Down) == true) {
        if (_frameKey > 7) {
            if (_snake[0]._nextDirection != (int)Direction::up && _snake[0]._nextDirection != (int)Direction::down) {
                _snake[0]._nextDirection = (int)Direction::down;
                _frameKey = 1;
            }
        }
    }
    if (_core->isButtonPressed(IDisplayModule::Button::Up) == true) {
        if (_frameKey > 7) {
            if (_snake[0]._nextDirection != (int)Direction::up && _snake[0]._nextDirection != (int)Direction::down) {
                _snake[0]._nextDirection = (int)Direction::up;
                _frameKey = 1;
            }
        }
    }
    if (_core->isButtonPressed(IDisplayModule::Button::Left) == true) {
        if (_frameKey > 7) {
            if (_snake[0]._nextDirection != (int)Direction::right && _snake[0]._nextDirection != (int)Direction::left) {
                _snake[0]._nextDirection = (int)Direction::left;
                _frameKey = 1;
            }
        }
    }
    if (_core->isButtonPressed(IDisplayModule::Button::Right) == true) {
        if (_frameKey > 7) {
            if (_snake[0]._nextDirection != (int)Direction::right && _snake[0]._nextDirection != (int)Direction::left) {
                _snake[0]._nextDirection = (int)Direction::right;
                _frameKey = 1;
            }
        }
    }
    if (_core->isButtonPressed(IDisplayModule::Button::Start) == true) {
        _end = false;
    }
    setGum(); //takes way too long
    if (_frameRate > 7 && _end == false) {
        headMoves();
        for (int i = _snake.size() - 2; i > 0; i--)
            bodyMoves(i);
        tailMoves();
        handleNew();
        collisionHimself();
    }
    _frameRate++;
    _frameKey++;
}

std::unique_ptr<IGameModule> gEpitechArcadeGetGameModuleHandle()
{
    return std::make_unique<Nibbler>();
}