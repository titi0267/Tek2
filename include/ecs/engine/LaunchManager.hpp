/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** LaunchManager
*/

#pragma once

#include "input/InputFile.hpp"
#include <stdexcept>
#include <filesystem>
#include <deque>

namespace ecs {
    class LaunchManager {
        int _nbPlayersHost;
        int _nbPlayers;
        std::deque<InputFile> _inputHost;
        std::deque<InputFile> _input;
        std::string _ipPort;

        public:
            LaunchManager()
            {
                _nbPlayers = 1;
                _nbPlayersHost = 1;
                reload();
            }
            ~LaunchManager() = default;
            void reload()
            {
                _inputHost.clear();
                _input.clear();
                std::string path = "assets/inputs";
                for (const auto &file : std::filesystem::directory_iterator(path)) {
                    InputFile a (file.path().u8string());
                    InputFile b (file.path().u8string());
                    _input.push_back(std::move(a));
                    _inputHost.push_back(std::move(b));
                }
                if (!std::filesystem::is_directory("inputs"))
                    return;
                path = "inputs";
                for (const auto &file : std::filesystem::directory_iterator(path)) {
                    try {
                        InputFile a (file.path().u8string());
                        InputFile b (file.path().u8string());
                        _input.push_back(std::move(a));
                        _inputHost.push_back(std::move(b));
                    }
                    catch (std::invalid_argument) {
                        continue;
                    }
                }
            }
            void modifyAt(bool host, InputFile file, size_t index)
            {
                if (index < 0 && index > 3)
                    return;
                if (host)
                    _inputHost[index] = std::move(file);
                _input[index] = std::move(file);
            }
            int getNbPlayers(bool host)
            {
                if (host)
                    return (_nbPlayersHost);
                return (_nbPlayers);
            }
            InputFile getAt(bool host, size_t index)
            {
                if (index < 0 && index > 3)
                    throw std::invalid_argument("Out of bounds");
                if (host)
                    return (std::move(_inputHost[index]));
                return (std::move(_input[index]));
            }
            void setNbPlayers(bool host, int nbPlayers)
            {
                if (_nbPlayers < 1 && _nbPlayers > 4)
                    return;
                if (host)
                    _nbPlayersHost = nbPlayers;
                else
                    _nbPlayers = nbPlayers;
            }
            std::string getName(bool host, int nbPlayer)
            {
                if (host)
                    return (_inputHost[nbPlayer].getName());
                return (_input[nbPlayer].getName());
            }
            std::string getKeyText(bool host, int nbPlayer, IBind::Binding bind)
            {
                if (host)
                    return (_inputHost[nbPlayer].getKeyText(bind));
                return (_input[nbPlayer].getKeyText(bind));
            }
            void swap(bool host, int nbPlayer)
            {
                if (host) {
                    if (_inputHost.size() <= nbPlayer)
                        return;
                    InputFile a = std::move(_inputHost[nbPlayer]);
                    InputFile b = std::move(_inputHost[_nbPlayersHost]);
                    _inputHost.erase(_inputHost.begin() + nbPlayer);
                    _inputHost.erase(_inputHost.begin() + _nbPlayersHost - 1);
                    _inputHost.push_back(std::move(a));
                    _inputHost.insert(_inputHost.begin() + nbPlayer, std::move(b));
                }
                else {
                    if (_input.size() <= nbPlayer)
                        return;
                    InputFile a = std::move(_input[nbPlayer]);
                    InputFile b = std::move(_input[_nbPlayers]);
                    _input.erase(_input.begin() + nbPlayer);
                    _input.erase(_input.begin() + _nbPlayers - 1);
                    _input.push_back(std::move(a));
                    _input.insert(_input.begin() + nbPlayer, std::move(b));
                }
            }
            bool getGamepad(bool host, int nbPlayer)
            {
                if (host)
                    return (_inputHost[nbPlayer].getGamepad());
                return (_input[nbPlayer].getGamepad());
            }
            void setIpPort(const std::string &ipPort)
            {
                _ipPort = ipPort;
            }
            const std::string &getIpPort()
            {
                return (_ipPort);
            }
    };
}
