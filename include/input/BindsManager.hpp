/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** BindsManager
*/

#pragma once

#include "InputFile.hpp"
#include <utility>
#include <stdexcept>

namespace ecs {
    class BindManager {
        InputFile _gamepad;
        InputFile _keyboard;
        bool _setOffGp;
        bool _setOffKb;
        public:
            BindManager() : _gamepad(true), _keyboard(false), _setOffGp(false), _setOffKb(false) {};
            ~BindManager() = default;
            void save(bool gamepad)
            {
                if (gamepad)
                    _gamepad.save();
                else
                    _keyboard.save();
            }
            void setName(bool gamepad, const std::string &name)
            {
                if (gamepad)
                    _gamepad.setName(name);
                else
                    _keyboard.setName(name);
            }
            void setKey(bool gamepad, IBind::Binding bind, int keyInt)
            {
                if (gamepad)
                    _gamepad.setKey(bind, keyInt);
                else
                    _keyboard.setKey(bind, keyInt);
            }
            int getKey(bool gamepad, IBind::Binding bind)
            {
                if (gamepad)
                    return (_gamepad.getKey(bind));
                return (_keyboard.getKey(bind));
            }
            std::string getKeyText(bool gamepad, IBind::Binding bind)
            {
                if (gamepad)
                    return (_gamepad.getKeyText(bind));
                return (_keyboard.getKeyText(bind));
            }
            void load(bool gamepad, const std::string &path)
            {
                try {
                    InputFile file(path);
                    if (gamepad)
                        _gamepad = file;
                    else
                        _keyboard = file;
                }
                catch (std::invalid_argument) {
                    throw std::invalid_argument("File does not exist or isn't correct!");
                }
            }
            void toggleSetOff(bool gamepad)
            {
                if (gamepad)
                    _setOffGp = !_setOffGp;
                else
                    _setOffKb = !_setOffKb;
            }
            bool getSetOff(bool gamepad)
            {
                if (gamepad)
                    return (_setOffGp);
                return (_setOffKb);
            }
        protected:
        private:
    };
}
