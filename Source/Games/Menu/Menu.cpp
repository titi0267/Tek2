/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-alexandre.frantz
** File description:
** Menu
*/

#include "Menu.hpp"
#include "../../Interface/Core.hpp"

Menu::Menu()
{
    _pixelPerCell = 16;
    _selected = Menu::Selected::Graphical;
    _maxLib = 0;
    _maxGame = 0;
    _menuMode = true;
    _indexGame = 0;
}

Menu::~Menu()
{
}

void Menu::readDir()
{
    std::string path = "./lib/";

    for (const auto & entry : std::filesystem::directory_iterator(path)) {
        _files.push_back(entry.path());
    }
}

void Menu::sortLibsGames()
{
    for (int i = 0; i < _files.size() ; i++) {
        try {
            if (_dl.openLib(_files[i].c_str()) == NULL) {
                throw (Error(dlerror()));
            }
            if (_dl.tryDownloadLib() != NULL) {
                if (_dl.openGame(_files[i].c_str()) == NULL)
                    throw (Error(dlerror()));
                if (_dl.tryDownloadGame() != NULL) {
                    throw (Error(_dl.tryDownloadGame()));
                }
                _games.push_back(_files[i]);
                _maxGame++;
                continue;
            }
            _libs.push_back(_files[i]);
            _maxLib++;
        } catch (Error e) {
            std::cout << e.what() << std::endl;
            continue;
        } catch (...) {
            std::cerr << "catch" << std::endl;
        }
    }
}

void Menu::chooseFirstLib(Core *coreHandle, const char *av)
{
    for (int i = 0; i < _libs.size(); i++) {
        if (strcmp(_libs[i].c_str(), av) == 0) {
                _dl.openLib(_libs[i].c_str());
                _dl.tryDownloadLib();
                coreHandle->loadLibs(_dl.getLib());
                _indexLib = i;
            break;
        }
    }
}

void Menu::chooseGame(Core *coreHandle)
{
    _dl.openGame(_games[_indexGame].c_str());
    _dl.tryDownloadGame();
    coreHandle->loadGames(_dl.getGame());
    _core = coreHandle;
}

void Menu::manageSelected()
{
    if (_core->isButtonPressed(Core::Button::Down)) {
        if (_selected == Menu::Selected::Graphical) _selected = Menu::Selected::Games;
        //if (_selected == Menu::Selected::Games) _selected = Menu::Selected::Score;
    }
    if (_core->isButtonPressed(Core::Button::Up)) {
        if (_selected == Menu::Selected::Games) _selected = Menu::Selected::Graphical;
        //if (_selected == Menu::Selected::Score) _selected = Menu::Selected::Games;
    }
    if (_selected == Menu::Selected::Graphical) {
        _sprite[7].texture->setCharColor(ICore::Color::black);
        _sprite[7].texture->setBackColor(ICore::Color::white);
        _sprite[8].texture->setCharColor(ICore::Color::black);
        _sprite[8].texture->setBackColor(ICore::Color::white);
        if (_core->isButtonPressed(Core::Button::Start)) {
            std::cout << "Enter lib" << std::endl;
        }
        if (_core->isButtonPressed(Core::Button::Right)) {
            if (_indexLib + 1 != _maxLib)
                _indexLib++;
            else
                _indexLib = 0;
        }
        if (_core->isButtonPressed(Core::Button::Left)) {
            if (_indexLib - 1 != -1)
                _indexLib--;
            else
                _indexLib = _maxLib - 1;
        }
    } else if (_selected == Menu::Selected::Games) {
        _sprite[14].texture->setCharColor(ICore::Color::black);
        _sprite[14].texture->setBackColor(ICore::Color::white);
        _sprite[15].texture->setCharColor(ICore::Color::black);
        _sprite[15].texture->setBackColor(ICore::Color::white);
        if (_core->isButtonPressed(Core::Button::Right)) {
            if (_indexGame + 1 != _maxGame)
                _indexGame++;
            else
                _indexGame = 0;
        }
        if (_core->isButtonPressed(Core::Button::Left)) {
            if (_indexGame - 1 != -1)
                _indexGame--;
            else
                _indexGame = _maxGame - 1;
        }
        if (_core->isButtonPressed(Core::Button::Start)) {
            chooseGame(_core);
            _core->getGame()->init(_core);
            _menuMode = false;
        }

    } else {
        _sprite[9].texture->setCharColor(ICore::Color::blue);
        _sprite[9].texture->setBackColor(ICore::Color::white);
        _sprite[10].texture->setCharColor(ICore::Color::blue);
        _sprite[10].texture->setBackColor(ICore::Color::white);
        _sprite[11].texture->setCharColor(ICore::Color::blue);
        _sprite[11].texture->setBackColor(ICore::Color::white);
        _sprite[12].texture->setCharColor(ICore::Color::blue);
        _sprite[12].texture->setBackColor(ICore::Color::white);
        _sprite[13].texture->setCharColor(ICore::Color::blue);
        _sprite[13].texture->setBackColor(ICore::Color::white);
    }
}

void Menu::init(Core *coreHandle, char *av)
{
    int i = 0;
    ICore::Vector2u windowSize{1920, 1080};
    ICore::Vector2u background{0, 0};
    ICore::Vector2u title{480, 64};
    ICore::Vector2u leftArrow{48, 416};
    ICore::Vector2u rightArrow{1772, 416};
    ICore::Vector2u score{800, 900};

    coreHandle->openWindow(windowSize);
    /*_sprite.push_back({background, coreHandle->loadTexture("./Assets/Menu/bck.png", ' ', ICore::Color::black, ICore::Color::black, _pixelPerCell, _pixelPerCell)});
    _sprite.push_back({title,coreHandle->loadTexture("./Assets/Menu/title.png", 'A', ICore::Color::red, ICore::Color::white, _pixelPerCell, _pixelPerCell)});
    _sprite.push_back({{title.x, title.y+_pixelPerCell},coreHandle->loadTexture("", 'R', ICore::Color::red, ICore::Color::white, _pixelPerCell, _pixelPerCell)});
    _sprite.push_back({{title.x, title.y+_pixelPerCell*2},coreHandle->loadTexture("", 'C', ICore::Color::red, ICore::Color::white, _pixelPerCell, _pixelPerCell)});
    _sprite.push_back({{title.x, title.y+_pixelPerCell*3},coreHandle->loadTexture("", 'A', ICore::Color::red, ICore::Color::white, _pixelPerCell, _pixelPerCell)});
    _sprite.push_back({{title.x, title.y+_pixelPerCell*4},coreHandle->loadTexture("", 'D', ICore::Color::red, ICore::Color::white, _pixelPerCell, _pixelPerCell)});
    _sprite.push_back({{title.x, title.y+_pixelPerCell*5},coreHandle->loadTexture("", 'E', ICore::Color::red, ICore::Color::white, _pixelPerCell, _pixelPerCell)});
    _sprite.push_back({leftArrow, coreHandle->loadTexture("./Assets/Menu/leftArrow.png", '<', ICore::Color::white, ICore::Color::black, _pixelPerCell, _pixelPerCell)});
    _sprite.push_back({rightArrow, coreHandle->loadTexture("./Assets/Menu/rightArrow.png", '>', ICore::Color::white, ICore::Color::black, _pixelPerCell, _pixelPerCell)});
    _sprite.push_back({score, coreHandle->loadTexture("./Assets/Menu/ARCADE_N.ttf", 'S', ICore::Color::white, ICore::Color::blue, _pixelPerCell, _pixelPerCell)});
    _sprite.push_back({{score.x+_pixelPerCell, score.y}, coreHandle->loadTexture("./Assets/Menu/ARCADE_N.ttf", 'C', ICore::Color::white, ICore::Color::blue, _pixelPerCell, _pixelPerCell)});
    _sprite.push_back({{score.x+_pixelPerCell*2, score.y}, coreHandle->loadTexture("./Assets/Menu/ARCADE_N.ttf", 'O', ICore::Color::white, ICore::Color::blue, _pixelPerCell, _pixelPerCell)});
    _sprite.push_back({{score.x+_pixelPerCell*3, score.y}, coreHandle->loadTexture("./Assets/Menu/ARCADE_N.ttf", 'R', ICore::Color::white, ICore::Color::blue, _pixelPerCell, _pixelPerCell)});
    _sprite.push_back({{score.x+_pixelPerCell*4, score.y}, coreHandle->loadTexture("./Assets/Menu/ARCADE_N.ttf", 'E', ICore::Color::white, ICore::Color::blue, _pixelPerCell, _pixelPerCell)});
    _sprite.push_back({{leftArrow.x, leftArrow.y+80}, coreHandle->loadTexture("./Assets/Menu/leftArrow.png", '<', ICore::Color::white, ICore::Color::black, _pixelPerCell, _pixelPerCell)});
    _sprite.push_back({{rightArrow.x, rightArrow.y+80}, coreHandle->loadTexture("./Assets/Menu/rightArrow.png", '>', ICore::Color::white, ICore::Color::black, _pixelPerCell, _pixelPerCell)});*/
    
    
    _sprite.push_back({background, coreHandle->loadTexture("./Assets/Menu/bck.png", ' ', ICore::Color::black, ICore::Color::black, _pixelPerCell, _pixelPerCell)});
    _sprite.push_back({{title.x+_pixelPerCell, title.y},coreHandle->loadTexture("./Assets/Menu/ARCADE_N.ttf", 'R', ICore::Color::red, ICore::Color::white, _pixelPerCell, _pixelPerCell)});
    _sprite.push_back({{title.x+_pixelPerCell*2, title.y},coreHandle->loadTexture("./Assets/Menu/ARCADE_N.ttf", 'C', ICore::Color::red, ICore::Color::white, _pixelPerCell, _pixelPerCell)});
    _sprite.push_back({{title.x+_pixelPerCell*3, title.y},coreHandle->loadTexture("./Assets/Menu/ARCADE_N.ttf", 'A', ICore::Color::red, ICore::Color::white, _pixelPerCell, _pixelPerCell)});
    _sprite.push_back({{title.x+_pixelPerCell*4, title.y},coreHandle->loadTexture("./Assets/Menu/ARCADE_N.ttf", 'D', ICore::Color::red, ICore::Color::white, _pixelPerCell, _pixelPerCell)});
    _sprite.push_back({{title.x+_pixelPerCell*5, title.y},coreHandle->loadTexture("./Assets/Menu/ARCADE_N.ttf", 'E', ICore::Color::red, ICore::Color::white, _pixelPerCell, _pixelPerCell)});
    _sprite.push_back({title,coreHandle->loadTexture("./Assets/Menu/title.png", 'A', ICore::Color::red, ICore::Color::white, _pixelPerCell, _pixelPerCell)});
    _sprite.push_back({leftArrow, coreHandle->loadTexture("./Assets/Menu/leftArrow.png", '<', ICore::Color::white, ICore::Color::black, _pixelPerCell, _pixelPerCell)});
    _sprite.push_back({rightArrow, coreHandle->loadTexture("./Assets/Menu/rightArrow.png", '>', ICore::Color::white, ICore::Color::black, _pixelPerCell, _pixelPerCell)});
    _sprite.push_back({score, coreHandle->loadTexture("./Assets/Menu/ARCADE_N.ttf", 'S', ICore::Color::white, ICore::Color::blue, _pixelPerCell*4, _pixelPerCell)});
    _sprite.push_back({{score.x+_pixelPerCell*4, score.y}, coreHandle->loadTexture("./Assets/Menu/ARCADE_N.ttf", 'C', ICore::Color::white, ICore::Color::blue, _pixelPerCell*4, _pixelPerCell)});
    _sprite.push_back({{score.x+_pixelPerCell*8, score.y}, coreHandle->loadTexture("./Assets/Menu/ARCADE_N.ttf", 'O', ICore::Color::white, ICore::Color::blue, _pixelPerCell*4, _pixelPerCell)});
    _sprite.push_back({{score.x+_pixelPerCell*12, score.y}, coreHandle->loadTexture("./Assets/Menu/ARCADE_N.ttf", 'R', ICore::Color::white, ICore::Color::blue, _pixelPerCell*4, _pixelPerCell)});
    _sprite.push_back({{score.x+_pixelPerCell*16, score.y}, coreHandle->loadTexture("./Assets/Menu/ARCADE_N.ttf", 'E', ICore::Color::white, ICore::Color::blue, _pixelPerCell*4, _pixelPerCell)});
    _sprite.push_back({{leftArrow.x, leftArrow.y+256}, coreHandle->loadTexture("./Assets/Menu/leftArrow.png", '<', ICore::Color::white, ICore::Color::black, _pixelPerCell, _pixelPerCell)});
    _sprite.push_back({{rightArrow.x, rightArrow.y+256}, coreHandle->loadTexture("./Assets/Menu/rightArrow.png", '>', ICore::Color::white, ICore::Color::black, _pixelPerCell, _pixelPerCell)});

    coreHandle->setFramerate(60);
    coreHandle->setPixelsPerCell(_pixelPerCell);
    _core = coreHandle;
}

void Menu::draw()
{
    _core->getLib()->display();
    if (_menuMode == true) {
        _core->clearScreen(ICore::Color::black);
        for (int i = 0; i < _sprite.size(); i++) {
            _core->renderSprite(_sprite[i]);
        }
        for (unsigned i = 0, x = 450; i != _libs[_indexLib].length(); i++) {
            _core->renderSprite({{x, 400}, _core->loadTexture("./Assets/Menu/ARCADE_N.ttf", (char)_libs[_indexLib].at(i), ICore::Color::red, ICore::Color::white, _pixelPerCell, _pixelPerCell)});
            x += 20;
        }
        for (unsigned i = 0, z = 450; i != _games[_indexGame].length(); i++) {
            _core->renderSprite({{z, 700}, _core->loadTexture("./Assets/Menu/ARCADE_N.ttf", (char)_games[_indexGame].at(i), ICore::Color::red, ICore::Color::white, _pixelPerCell, _pixelPerCell)});
            z += 20;
        }
    } else {
        _core->getGame()->draw();
    }
}

void Menu::update()
{
    _core->getLib()->update();
    if (_menuMode == true)
        manageSelected();
    else
        _core->getGame()->update();
}
