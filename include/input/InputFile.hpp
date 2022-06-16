/*
** EPITECH PROJECT, 2022
** input
** File description:
** InputFile
*/

#pragma once

#include <string>
#include <vector>
#include <memory>
#include "IBind.hpp"

class InputFile {
    public:
        InputFile(const std::string &path);
        InputFile(bool gamepad);
        InputFile(InputFile &&other)
        {
            _name = other._name;
            _gamepad = other._gamepad;
            _binds = std::move(_binds);
        }
        void operator=(const InputFile &other)
        {
            _name = other._name;
            _gamepad = other._gamepad;
            _binds = std::move(_binds);
        }
        ~InputFile();
        void save();
        void setName(const std::string &name);
        void setKey(IBind::Binding bind, int keyInt);
        int getKey(IBind::Binding bind);
        std::string getKeyText(IBind::Binding bind);

    protected:
        std::string _name;
        bool _gamepad;
        std::unique_ptr<IBind> _binds;
    private:
};
