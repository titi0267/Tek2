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
            }
            _libs.push_back(_files[i]);
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
                coreHandle->addNewScore(1);
                coreHandle->loadLibs(_dl.getLib());
            break;
        }
    }

    for (int i = 0; i < _games.size(); i++) {
        std::cout << "games are : "<< _games[i] << std::endl;
        //if (_libs[i] == av)
    }
    //return coreHandle;
}

void Menu::manageSelected()
{
    if (_core->isButtonPressed(Core::Button::Down)) {
        if (_selected == Menu::Selected::Graphical) _selected = Menu::Selected::Games;
        if (_selected == Menu::Selected::Games) _selected = Menu::Selected::Score;
    }
    if (_core->isButtonPressed(Core::Button::Up)) {
        if (_selected == Menu::Selected::Games) _selected = Menu::Selected::Graphical;
        if (_selected == Menu::Selected::Score) _selected = Menu::Selected::Games;
    }
    if (_selected == Menu::Selected::Graphical) {
        _sprite[7].texture->setCharColor(ICore::Color::black);
        _sprite[7].texture->setBackColor(ICore::Color::white);
        _sprite[8].texture->setCharColor(ICore::Color::black);
        _sprite[8].texture->setBackColor(ICore::Color::white);
    } else if (_selected == Menu::Selected::Games) {
        _sprite[14].texture->setCharColor(ICore::Color::black);
        _sprite[14].texture->setBackColor(ICore::Color::white);
        _sprite[15].texture->setCharColor(ICore::Color::black);
        _sprite[15].texture->setBackColor(ICore::Color::white);
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
    ICore::Vector2u leftArrow{16, 352};
    ICore::Vector2u rightArrow{1554, 352};
    ICore::Vector2u score{920, 1032};

    coreHandle->openWindow(windowSize);
    _sprite.push_back({background, coreHandle->loadTexture("./Assets/Menu/bck.png", ' ', ICore::Color::black, ICore::Color::black, _pixelPerCell, _pixelPerCell)});
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
    _sprite.push_back({{rightArrow.x, rightArrow.y+80}, coreHandle->loadTexture("./Assets/Menu/rightArrow.png", '>', ICore::Color::white, ICore::Color::black, _pixelPerCell, _pixelPerCell)});
    coreHandle->setFramerate(60);
    coreHandle->setPixelsPerCell(_pixelPerCell);
    _core = coreHandle;
}

void Menu::draw()
{
    _core->clearScreen(ICore::Color::black);
    for (int i = 0; i < _sprite.size(); i++)
        _core->renderSprite(_sprite[i]);
}

void Menu::update()
{
    manageSelected();
}
