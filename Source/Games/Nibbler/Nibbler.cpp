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
    _snakeSize = 4;
    constructMap();
    _frameRate = 1;
    _counter = 0;
    _frameKey = 1;
    _frameNext = 1;
    std::cout << "nibbler builded" << std::endl;
}

Nibbler::~Nibbler()
{
}

void Nibbler::init(ICore *coreHandle)
{
    ICore::Vector2u windowSize{40, 22};
    ICore::Vector2u border{0, 0};
    ICore::Vector2u grass{0, 0};
    ICore::Vector2u gums{9, 3};
    ICore::Vector2u head{10, 5};
    ICore::Vector2u body{9, 5};
    ICore::Vector2u tail{7, 5};

    coreHandle->openWindow(windowSize);
    _sprite.push_back({{grass, coreHandle->loadTexture("./Assets/Nibbler/Grass.png", ' ', ICore::Color::black, ICore::Color::black, 16, 16)}, {grass, coreHandle->loadTexture("./Assets/Nibbler/Grass.png", ' ', ICore::Color::black, ICore::Color::black, 16, 16)}, (int)Direction::up, (int)Direction::up, false});
    _sprite.push_back({{gums, coreHandle->loadTexture("./Assets/Nibbler/Gums.png", 'O', ICore::Color::red, ICore::Color::black, 16, 16)}, {gums, coreHandle->loadTexture("./Assets/Nibbler/Gums.png", 'O', ICore::Color::red, ICore::Color::black, 16, 16)}, (int)Direction::up, (int)Direction::up, false});
    _sprite.push_back({{border, coreHandle->loadTexture("./Assets/Nibbler/Border.png", '#', ICore::Color::black, ICore::Color::black, 16, 16)}, {border, coreHandle->loadTexture("./Assets/Nibbler/Border.png", '#', ICore::Color::black, ICore::Color::black, 16, 16)}, (int)Direction::up,(int)Direction::up, false});
    _sprite.push_back({{head, coreHandle->loadTexture("./Assets/Nibbler/HeadUp.png", ' ', ICore::Color::red, ICore::Color::red, 16, 16)}, {head, coreHandle->loadTexture("./Assets/Nibbler/HeadUp.png", ' ', ICore::Color::red, ICore::Color::red, 16, 16)}, (int)Direction::up,(int)Direction::up, false});
    _sprite.push_back({{head, coreHandle->loadTexture("./Assets/Nibbler/HeadDown.png", ' ', ICore::Color::red, ICore::Color::red, 16, 16)}, {head, coreHandle->loadTexture("./Assets/Nibbler/HeadDown.png", ' ', ICore::Color::red, ICore::Color::red, 16, 16)}, (int)Direction::down,(int)Direction::down, false});
    _sprite.push_back({{head, coreHandle->loadTexture("./Assets/Nibbler/HeadRight.png", ' ', ICore::Color::red, ICore::Color::red, 16, 16)}, {head, coreHandle->loadTexture("./Assets/Nibbler/HeadRight.png", ' ', ICore::Color::red, ICore::Color::red, 16, 16)}, (int)Direction::right,(int)Direction::right, false});
    _sprite.push_back({{head, coreHandle->loadTexture("./Assets/Nibbler/HeadLeft.png", ' ', ICore::Color::red, ICore::Color::red, 16, 16)}, {head, coreHandle->loadTexture("./Assets/Nibbler/HeadLeft.png", ' ', ICore::Color::red, ICore::Color::red, 16, 16)}, (int)Direction::left, (int)Direction::left, false});
    /*up*/_sprite.push_back({{body, coreHandle->loadTexture("./Assets/Nibbler/BodyVertical.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, {body, coreHandle->loadTexture("./Assets/Nibbler/BodyVertical.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, (int)Direction::up, (int)Direction::up, false});
    /*down*/_sprite.push_back({{body, coreHandle->loadTexture("./Assets/Nibbler/BodyVertical.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, {body, coreHandle->loadTexture("./Assets/Nibbler/BodyVertical.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, (int)Direction::down, (int)Direction::down, false});
    /*right*/_sprite.push_back({{body, coreHandle->loadTexture("./Assets/Nibbler/BodyHorizontal.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, {body, coreHandle->loadTexture("./Assets/Nibbler/BodyHorizontal.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, (int)Direction::right,(int)Direction::right, false});
    /*left*/_sprite.push_back({{body, coreHandle->loadTexture("./Assets/Nibbler/BodyHorizontal.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, {body, coreHandle->loadTexture("./Assets/Nibbler/BodyHorizontal.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, (int)Direction::left,(int)Direction::left, false});
    /*rightup11*/_sprite.push_back({{body, coreHandle->loadTexture("./Assets/Nibbler/BodyCornerLeftUp.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, {body, coreHandle->loadTexture("./Assets/Nibbler/BodyCornerLeftUp.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, (int)Direction::right,(int)Direction::up, true});
    /*downleft12*/_sprite.push_back({{body, coreHandle->loadTexture("./Assets/Nibbler/BodyCornerLeftUp.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, {body, coreHandle->loadTexture("./Assets/Nibbler/BodyCornerLeftUp.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, (int)Direction::down,(int)Direction::left, true});
    /*leftup13*/_sprite.push_back({{body, coreHandle->loadTexture("./Assets/Nibbler/BodyCornerRightUp.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, {body, coreHandle->loadTexture("./Assets/Nibbler/BodyCornerRightUp.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, (int)Direction::left, (int)Direction::up, true});
    /*downright14*/_sprite.push_back({{body, coreHandle->loadTexture("./Assets/Nibbler/BodyCornerRightUp.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, {body, coreHandle->loadTexture("./Assets/Nibbler/BodyCornerRightUp.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, (int)Direction::down, (int)Direction::right, true});
    /*upleft15*/_sprite.push_back({{body, coreHandle->loadTexture("./Assets/Nibbler/BodyCornerLeftDown.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, {body, coreHandle->loadTexture("./Assets/Nibbler/BodyCornerLeftDown.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, (int)Direction::up,(int)Direction::left, true});
    /*rightdown16*/_sprite.push_back({{body, coreHandle->loadTexture("./Assets/Nibbler/BodyCornerLeftDown.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, {body, coreHandle->loadTexture("./Assets/Nibbler/BodyCornerLeftDown.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, (int)Direction::right,(int)Direction::down, true});
    /*upright17*/_sprite.push_back({{body, coreHandle->loadTexture("./Assets/Nibbler/BodyCornerRightDown.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, {body, coreHandle->loadTexture("./Assets/Nibbler/BodyCornerRightDown.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, (int)Direction::up,(int)Direction::right ,true});
    /*leftdown18*/_sprite.push_back({{body, coreHandle->loadTexture("./Assets/Nibbler/BodyCornerRightDown.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, {body, coreHandle->loadTexture("./Assets/Nibbler/BodyCornerRightDown.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)}, (int)Direction::left,(int)Direction::down ,true});
    _sprite.push_back({{tail, coreHandle->loadTexture("./Assets/Nibbler/TailUp.png", ' ', ICore::Color::cyan, ICore::Color::cyan, 16, 16)}, {tail, coreHandle->loadTexture("./Assets/Nibbler/TailUp.png", ' ', ICore::Color::cyan, ICore::Color::cyan, 16, 16)}, (int)Direction::up,(int)Direction::up, false});
    _sprite.push_back({{tail, coreHandle->loadTexture("./Assets/Nibbler/TailDown.png", ' ', ICore::Color::cyan, ICore::Color::cyan, 16, 16)}, {tail, coreHandle->loadTexture("./Assets/Nibbler/TailDown.png", ' ', ICore::Color::cyan, ICore::Color::cyan, 16, 16)}, (int)Direction::down,(int)Direction::down, false});
    _sprite.push_back({{tail, coreHandle->loadTexture("./Assets/Nibbler/TailLeft.png", ' ', ICore::Color::cyan, ICore::Color::cyan, 16, 16)}, {tail, coreHandle->loadTexture("./Assets/Nibbler/TailLeft.png", ' ', ICore::Color::cyan, ICore::Color::cyan, 16, 16)}, (int)Direction::left,(int)Direction::left, false});
    _sprite.push_back({{tail, coreHandle->loadTexture("./Assets/Nibbler/TailRight.png", ' ', ICore::Color::cyan, ICore::Color::cyan, 16, 16)}, {tail, coreHandle->loadTexture("./Assets/Nibbler/TailRight.png", ' ', ICore::Color::cyan, ICore::Color::cyan, 16, 16)}, (int)Direction::right,(int)Direction::right, false});
    constructSnake();
    coreHandle->setFramerate(30);
    coreHandle->setPixelsPerCell(8);
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
    ICore::Vector2u bodyPos{_sprite[9]._sprt.pixelPosition.x - 1, _sprite[9]._sprt.pixelPosition.y};

    _snake.push_back({{_sprite[5]._sprt.pixelPosition , _sprite[5]._sprt.texture}, {_sprite[5]._sprt.pixelPosition , _sprite[5]._sprt.texture}, _sprite[5]._direction, _sprite[5]._direction, false});
    _snake.push_back({{_sprite[9]._sprt.pixelPosition, _sprite[9]._sprt.texture}, {_sprite[9]._sprt.pixelPosition, _sprite[9]._sprt.texture}, _sprite[9]._direction,_sprite[9]._direction, false});
    _snake.push_back({{bodyPos, _sprite[9]._sprt.texture}, {bodyPos, _sprite[9]._sprt.texture}, _sprite[9]._direction,_sprite[9]._direction, false});
    _snake.push_back({{_sprite[22]._sprt.pixelPosition, _sprite[18]._sprt.texture}, {_sprite[22]._sprt.pixelPosition, _sprite[22]._sprt.texture}, _sprite[22]._direction,_sprite[22]._direction, false});
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
    if (_sprite[getDirection(0) + 3]._sprt.pixelPosition.x == random)
        return true;
    return false;
}

/*   check snake's head position compared with gum position in Y  */
bool Nibbler::checkSnakeHeadPosY(unsigned random)
{
    if (_sprite[getDirection(0) + 3]._sprt.pixelPosition.x == random)
        return true;
    return false;
}

/*  Add new body section when gum position matches with snake's head position  */
void Nibbler::gumEated()
{
    std::deque<Snake>::iterator it = (_snake.end() - 1);

    _snakeSize++;
    _snake.insert(it, {_snake[_snake.size() - 1]._sprt.pixelPosition, _snake[_snake.size() - 1]._sprt.texture});
    _addNewBody = true;
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
    int randomX;
    int randomY;

    if (_gum == true) {
        if (checkSnakeHeadPosX(_sprite[1]._sprt.pixelPosition.x) == false && checkSnakeHeadPosY(_sprite[1]._sprt.pixelPosition.y) == false)
            gumEated();
    }
    if (_gum == false) {
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
    }
}

/**************************************/
/*                                    */
/*    Get snake's head direction :    */
/*        - Up    : 0                 */
/*        - Down  : 1                 */
/*        - Right : 2                 */
/*        - Left  : 3                 */
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
        _snake[1]._nextDirection = _sprite[4]._direction;
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
        _snake[0]._nextSprt.pixelPosition.y--;
        _snake[0]._nextSprt.texture = _sprite[3]._sprt.texture;
        break;
    case (int)Direction::down:
        _snake[0]._nextSprt.pixelPosition.y++;
        _snake[0]._nextSprt.texture = _sprite[4]._sprt.texture;
        break;
    case (int)Direction::right:
        _snake[0]._nextSprt.pixelPosition.x++;
        _snake[0]._nextSprt.texture = _sprite[5]._sprt.texture;
        break;
    case (int)Direction::left:
        _snake[0]._nextSprt.pixelPosition.x--;
        _snake[0]._nextSprt.texture = _sprite[6]._sprt.texture;
        break;
    default:
        break;
    }
    _frameRate = 1;
}

void Nibbler::bodyMoves(int i)
{
    _snake[i]._nextDirection = _snake[i - 1]._nextDirection;
    switch (_snake[i]._direction)
    {
    case (int)Direction::up:
        _snake[i]._nextSprt.pixelPosition.y--;
        chooseCorner(i);
        break;
    case (int)Direction::down:
        _snake[i]._nextSprt.pixelPosition.y++;
        chooseCorner(i);
        break;
    case (int)Direction::left:
        _snake[i]._nextSprt.pixelPosition.x--;
        chooseCorner(i);
        break;
    case (int)Direction::right:
        _snake[i]._nextSprt.pixelPosition.x++;
        chooseCorner(i);
        break;
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
                _snake[i]._nextSprt.texture = _sprite[7]._sprt.texture;
                _snake[i]._nextDirection = _sprite[7]._nextDirection;
            }
        break;
        case (int)Direction::down:
            if (_snake[i]._nextDirection == (int)Direction::right)
                rightCorner(i);
            else if (_snake[i]._nextDirection == (int)Direction::left) {
                leftCorner(i);
            } else {
                _snake[i]._nextSprt.texture = _sprite[8]._sprt.texture;
                _snake[i]._nextDirection = _sprite[8]._nextDirection;
            }
        break;
        case (int)Direction::left:
            if (_snake[i]._nextDirection == (int)Direction::up) {
                upCorner(i);
            } else if (_snake[i]._nextDirection == (int)Direction::down) {
                downCorner(i);
            } else {
                _snake[i]._nextSprt.texture = _sprite[10]._sprt.texture;
                _snake[i]._nextDirection = _sprite[10]._nextDirection;
            }
        break;
        case (int)Direction::right:
            if (_snake[i]._nextDirection == (int)Direction::up) {
                upCorner(i);
            } else if (_snake[i]._nextDirection == (int)Direction::down) {
                downCorner(i);
            } else {
                _snake[i]._nextSprt.texture = _sprite[9]._sprt.texture;
                _snake[i]._nextDirection = _sprite[9]._nextDirection;
            }
        break;
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
                _snake[i]._nextSprt.texture = _sprite[13]._sprt.texture;
                _snake[i]._nextDirection = _sprite[13]._nextDirection;
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
            _snake[i]._nextSprt.texture = _sprite[17]._sprt.texture;
            _snake[i]._nextDirection = _sprite[17]._nextDirection;
        }
        else if (_snake[i - 1]._nextDirection == (int)Direction::left) {
            _snake[i]._nextSprt.texture = _sprite[13]._sprt.texture;
            _snake[i]._nextDirection = _sprite[13]._nextDirection;
        }
        break;
    case (int)Direction::down:
        if (_snake[i - 1]._nextDirection == (int)Direction::right) {
            _snake[i]._nextSprt.texture = _sprite[14]._sprt.texture;
            _snake[i]._nextDirection = _sprite[14]._nextDirection;
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
            if (_map[i] == '#')
                _core->renderSprite({{_sprite[2]._sprt.pixelPosition.x + z, _sprite[2]._sprt.pixelPosition.y + y}, _sprite[2]._sprt.texture});
            if (_map[i] == ' ')
                _core->renderSprite({{_sprite[0]._sprt.pixelPosition.x + z, _sprite[0]._sprt.pixelPosition.y + y}, _sprite[0]._sprt.texture});
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
        if (_frameNext > 6) {
            for (int i = _snake.size() - 1; i != -1; i--) {
                _snake[i]._sprt = _snake[i]._nextSprt;
                _snake[i]._direction = _snake[i]._nextDirection;
            }
            std::cout << "print snake x:";
            std::cout << _snake[0]._nextSprt.pixelPosition.x << " & y:"<< std::endl;
            std::cout << _snake[0]._nextSprt.pixelPosition.y << std::endl;
            _frameNext = 1;
        }
        _frameNext++;
}

void Nibbler::update()
{
    if (_core->isButtonPressed(IDisplayModule::Button::Down) == true) {
        if (_frameKey > 6) {
            if (_snake[0]._nextDirection != (int)Direction::up && _snake[0]._nextDirection != (int)Direction::down) {
                _snake[0]._nextDirection = (int)Direction::down;
                _frameKey = 1;
            }
        }
    }
    if (_core->isButtonPressed(IDisplayModule::Button::Up) == true) {
        if (_frameKey > 6) {
            if (_snake[0]._nextDirection != (int)Direction::up && _snake[0]._nextDirection != (int)Direction::down) {
                _snake[0]._nextDirection = (int)Direction::up;
                _frameKey = 1;
            }
        }
    }
    if (_core->isButtonPressed(IDisplayModule::Button::Left) == true) {
        if (_frameKey > 6) {
            if (_snake[0]._nextDirection != (int)Direction::right && _snake[0]._nextDirection != (int)Direction::left) {
                _snake[0]._nextDirection = (int)Direction::left;
                _frameKey = 1;
            }
        }
    }
    if (_core->isButtonPressed(IDisplayModule::Button::Right) == true) {
        if (_frameKey > 6) {
            if (_snake[0]._nextDirection != (int)Direction::right && _snake[0]._nextDirection != (int)Direction::left) {
                _snake[0]._nextDirection = (int)Direction::right;
                _frameKey = 1;
            }
        }
    }
    if (_frameRate > 6) {
        headMoves();
        for (int i = _snake.size() - 2; i > 0; i--)
            bodyMoves(i);
    }
    _frameRate++;
    _frameKey++;
    //setGum(); //takes way too long
}

std::unique_ptr<IGameModule> gEpitechArcadeGetGameModuleHandle()
{
    return std::make_unique<Nibbler>();
}