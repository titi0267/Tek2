/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-alexandre.frantz
** File description:
** Menu
*/

#include "Menu.hpp"

Menu::Menu()
{
    //_pixelPerCell = 16;
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
        std::cout << _files[i] << std::endl;
        _dl.openLib(_files[i].c_str());
        if (dlerror() != NULL)
            continue;
        _dl.tryDownloadLib();
        if (dlerror() != NULL) {
            _dl.closeLib();
            _dl.openGame(_files[i].c_str());
            if (dlerror() != NULL)
                continue;
            _dl.tryDownloadGame();
            if (dlerror() != NULL)
                _dl.closeGame();
            else
                _games.push_back(_files[i]);
        } else {
                _libs.push_back(_files[i]);
        }
    }
}

bool Menu::chooseFirstLib(char *av)
{
    for (int i = 0; i < _libs.size(); i++) {
        std::cout << "libs are : "<< _libs[i] << std::endl;
        if (_libs[i].c_str() == av) {
            std::cout << "open " << _libs[i] << std::endl;
            _dl.openLib(av);
            if (dlerror() != NULL) {
                std::cerr << dlerror() << std::endl;
                exit(ERROR);
            }
            _dl.tryDownloadLib();
            if (dlerror() != NULL) {
                std::cerr << dlerror() << std::endl;
                exit(ERROR);
            }
            _core->loadLibs(_dl.getLib());
            std::cout << "load " << _libs[i];
            break;
        }
    }

    for (int i = 0; i < _games.size(); i++) {
        std::cout << "games are : "<< _games[i] << std::endl;
        //if (_libs[i] == av)
    }
    return false;
}

void Menu::init(Core *coreHandle, char *av)
{
    int i = 0;
    ICore::Vector2u windowSize{1920, 1080};
    ICore::Vector2u windowSize2{11, 11};
    ICore::Vector2u windowSize3{10, 11};
    ICore::Vector2u windowSize4{10, 12};
    ICore::Vector2u windowSize5{10, 13};

    readDir(); //list dir
    sortLibsGames(); //sort in _games & _libs
    //coreHandle->openWindow(windowSize);
    /*_sprite.push_back({windowSize2, coreHandle->loadTexture("./Assets/Menu/Background.jpg", '*', ICore::Color::black, ICore::Color::red, 612, 437)});
    _sprite.push_back({windowSize3, coreHandle->loadTexture("./Assets/Menu/Background.jpg", '|', ICore::Color::black, ICore::Color::magenta, 612, 437)});
    _sprite.push_back({windowSize4, coreHandle->loadTexture("./Assets/Menu/Background.jpg", '/', ICore::Color::black, ICore::Color::magenta, 612, 437)});
    _sprite.push_back({windowSize5, coreHandle->loadTexture("./Assets/Menu/Background.jpg", '*', ICore::Color::black, ICore::Color::cyan, 612, 437)});
    
    coreHandle->setFramerate(60);
    coreHandle->setPixelsPerCell(16);*/
    _core = coreHandle;
}

void Menu::draw()
{
    //_core->clearScreen(ICore::Color::black);
    //for (int i = 0)
    /*for (int i = 0; i < _sprite.size(); i++)
        _core->renderSprite(_sprite[i]);*/
}

void Menu::update()
{
    ;
}
