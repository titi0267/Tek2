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
    setDirection((int)Direction::right);
    constructMap();
    _frameRate = 1;
}

Nibbler::~Nibbler()
{
}

void Nibbler::init(ICore *coreHandle)
{
    ICore::Vector2u windowSize{290, 130};
    ICore::Vector2u border{0, 0};
    ICore::Vector2u grass{0, 0};
    ICore::Vector2u gums{9, 3};
    ICore::Vector2u head{10, 5};
    ICore::Vector2u body{9, 5};
    ICore::Vector2u tail{7, 5};

    coreHandle->openWindow(windowSize);
    _sprite.push_back({grass, coreHandle->loadTexture("./Assets/Nibbler/Grass.png", ' ', ICore::Color::black, ICore::Color::black, 16, 16)});
    _sprite.push_back({gums, coreHandle->loadTexture("./Assets/Nibbler/Gums.png", 'O', ICore::Color::red, ICore::Color::black, 16, 16)});
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Nibbler/Border.png", '#', ICore::Color::black, ICore::Color::black, 16, 16)});
    _sprite.push_back({head, coreHandle->loadTexture("./Assets/Nibbler/HeadUp.png", ' ', ICore::Color::red, ICore::Color::red, 16, 16)});
    _sprite.push_back({head, coreHandle->loadTexture("./Assets/Nibbler/HeadDown.png", ' ', ICore::Color::red, ICore::Color::red, 16, 16)});
    _sprite.push_back({head, coreHandle->loadTexture("./Assets/Nibbler/HeadRight.png", ' ', ICore::Color::red, ICore::Color::red, 16, 16)});
    _sprite.push_back({head, coreHandle->loadTexture("./Assets/Nibbler/HeadLeft.png", ' ', ICore::Color::red, ICore::Color::red, 16, 16)});
    _sprite.push_back({body, coreHandle->loadTexture("./Assets/Nibbler/BodyVertical.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)});
    _sprite.push_back({body, coreHandle->loadTexture("./Assets/Nibbler/BodyHorizontal.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)});
    _sprite.push_back({body, coreHandle->loadTexture("./Assets/Nibbler/BodyCornerLeftUp.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)});
    _sprite.push_back({body, coreHandle->loadTexture("./Assets/Nibbler/BodyCornerRightUp.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)});
    _sprite.push_back({body, coreHandle->loadTexture("./Assets/Nibbler/BodyCornerLeftDown.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)});
    _sprite.push_back({body, coreHandle->loadTexture("./Assets/Nibbler/BodyCornerRightDown.png", ' ', ICore::Color::magenta, ICore::Color::magenta, 16, 16)});
    _sprite.push_back({tail, coreHandle->loadTexture("./Assets/Nibbler/TailUp.png", ' ', ICore::Color::cyan, ICore::Color::cyan, 16, 16)});
    _sprite.push_back({tail, coreHandle->loadTexture("./Assets/Nibbler/TailDown.png", ' ', ICore::Color::cyan, ICore::Color::cyan, 16, 16)});
    _sprite.push_back({tail, coreHandle->loadTexture("./Assets/Nibbler/TailLeft.png", ' ', ICore::Color::cyan, ICore::Color::cyan, 16, 16)});
    _sprite.push_back({tail, coreHandle->loadTexture("./Assets/Nibbler/TailRight.png", ' ', ICore::Color::cyan, ICore::Color::cyan, 16, 16)});
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
        std::cout << "map here:" << std::endl;
    } else {
        //error
        std::cout << "fail here:" << std::endl;
    }
}

void Nibbler::constructSnake()
{
    ICore::Vector2u bodyPos{_sprite[8].pixelPosition.x - 1, _sprite[8].pixelPosition.y};

    _snake.push_back({_sprite[5].pixelPosition , _sprite[5].texture});
    _snake.push_back({_sprite[8].pixelPosition, _sprite[8].texture});
    _snake.push_back({bodyPos, _sprite[8].texture});
    _snake.push_back({_sprite[16].pixelPosition, _sprite[16].texture});
}

/*   check all snake's position compared with gum position in X   */
bool Nibbler::checkSnakePosX(unsigned random)
{
    for (int d = 0; d < _snake.size(); d++) {
        if (_snake[d].pixelPosition.x == random) //pas les bonnes sprites
            return true;
    }
    return false;
}

/*   check all snake's position compared with gum position in Y  */
bool Nibbler::checkSnakePosY(unsigned random)
{
    for (int d = 0; d < _snake.size(); d++) {
        if (_snake[d].pixelPosition.y == random)//pas les bonnes sprites ?
            return true;
    }
    return false;
}

/*   check snake's head position compared with gum position in X  */
bool Nibbler::checkSnakeHeadPosX(unsigned random)
{
    if (_sprite[getDirection() + 3].pixelPosition.x == random)
        return true;
    return false;
}

/*   check snake's head position compared with gum position in Y  */
bool Nibbler::checkSnakeHeadPosY(unsigned random)
{
    if (_sprite[getDirection() + 3].pixelPosition.x == random)
        return true;
    return false;
}

/*  Add new body section when gum position matches with snake's head position  */
void Nibbler::gumEated()
{
    std::deque<ICore::Sprite>::iterator it = (_snake.end() - 1);

    _snakeSize++;
    _snake.insert(it, {_snake[_snake.size() - 1].pixelPosition, _snake[_snake.size() - 1].texture});
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
        if (checkSnakeHeadPosX(_sprite[1].pixelPosition.x) == false && checkSnakeHeadPosY(_sprite[1].pixelPosition.y) == false)
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
        _sprite[1].pixelPosition.x = randomX;
        _sprite[1].pixelPosition.y = randomY;
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
int Nibbler::getDirection() const
{
    return _direction;
}

void Nibbler::setDirection(int direction)
{
    _direction = direction;
    switch (_direction)
    {
        case (int)Direction::up:
            _snake[0].texture = _sprite[3].texture;
            break;
        case (int)Direction::down:
            _snake[0].texture = _sprite[4].texture;
            break;
        case (int)Direction::right:
            _snake[0].texture = _sprite[5].texture;
            break;
        case (int)Direction::left:
            _snake[0].texture = _sprite[6].texture;
            break;
    }
}

void Nibbler::draw()
{
    _core->clearScreen(ICore::Color::black);
    for (int i = 0, y = 0, z = 0; i < _map.size(); i++, z++) {
        if (_map[i] == '#')
            _core->renderSprite({{_sprite[2].pixelPosition.x + z, _sprite[2].pixelPosition.y + y}, _sprite[2].texture});
        if (_map[i] == ' ')
            _core->renderSprite({{_sprite[0].pixelPosition.x + z, _sprite[0].pixelPosition.y + y}, _sprite[0].texture});
        if (_map[i] == '\n') {
            y++;
            z = -1;
        }
    }
    for (int i = 0; i < _snake.size(); i++) {
        _core->renderSprite(_snake[i]);
    }
    _core->renderSprite(_sprite[1]);
}

void Nibbler::updateSnakePos()
{
    for (int i = 0; i < _snake.size(); i++) {
        switch (getDirection()) {
            case (int)Direction::up:
                if (i == 0)
                    _snake[0].pixelPosition.y--;
                break;
            case (int)Direction::down:
                if (i == 0)
                    _snake[0].pixelPosition.y++;
                break;
            case (int)Direction::left:
                if (i == 0)
                    _snake[0].pixelPosition.x--;
                break;
            case (int)Direction::right:
                if (i == 0)
                    _snake[0].pixelPosition.x++;
                break;
        }
    }
    _frameRate = 1;
}

void Nibbler::update()
{
        if (_core->isButtonPressed(IDisplayModule::Button::Up) == true) {
        switch (getDirection()) {
            case (int)Direction::left:
                setDirection((int)Direction::up);
                break;
            case (int)Direction::right:
                setDirection((int)Direction::up);
                break;
            default:
                break;
        }
    }
    if (_core->isButtonPressed(IDisplayModule::Button::Down) == true) {
        switch (getDirection()) {
            case (int)Direction::left:
                setDirection((int)Direction::down);
                break;
            case (int)Direction::right:
                setDirection((int)Direction::down);
                break;
            default:
                break;
        }
    }
    if (_core->isButtonPressed(IDisplayModule::Button::Left) == true) {
        switch (getDirection()) {
            case (int)Direction::up:
                setDirection((int)Direction::left);
                break;
            case (int)Direction::down:
                setDirection((int)Direction::left);
                break;
            default:
                break;
        }
    }
    if (_core->isButtonPressed(IDisplayModule::Button::Right) == true) {
        switch (getDirection())
        {
            case (int)Direction::up:
                setDirection((int)Direction::right);
                break;
            case (int)Direction::down:
                setDirection((int)Direction::right);
                break;
            default:
                break;
        }
    }
    setGum();
    if (_frameRate % 20 == 0)
        updateSnakePos();
    _frameRate++;
}

std::unique_ptr<IGameModule> gEpitechArcadeGetGameModuleHandle()
{
    return std::make_unique<Nibbler>();
}