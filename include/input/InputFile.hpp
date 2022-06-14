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
        ~InputFile();
        void save();
        void setName(const std::string &name);

    protected:
        std::string _name;
        bool _gamepad;
        std::unique_ptr<IBind> _binds;
    private:
};
