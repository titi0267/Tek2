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
#include <iostream>

namespace ecs {
    class BindManager {
        InputFile _gamepad;
        InputFile _keyboard;
        std::string _loadGp;
        std::string _loadKb;
        bool _setOffGp;
        bool _setOffKb;
        bool _recordingGp;
        bool _textInputGp;
        bool _recordingKb;
        bool _textInputKb;
        public:
            BindManager() : _gamepad(true), _keyboard(false), _setOffGp(false), _setOffKb(false), _recordingGp(false), _recordingKb(false), _textInputGp(false), _textInputKb(false) {};
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
                        _gamepad = std::move(file);
                    else
                        _keyboard = std::move(file);
                }
                catch (std::invalid_argument) {
                    std::cerr << "Bad input file" << std::endl;
                    //throw std::invalid_argument("File does not exist or isn't correct!");
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
            void toggleRecording(bool gamepad)
            {
                if (gamepad)
                    _recordingGp = !_recordingGp;
                else
                    _recordingKb = !_recordingKb;
            }
            bool getRecording(bool gamepad)
            {
                if (gamepad)
                    return (_recordingGp);
                return (_recordingKb);
            }
            void toggleTextInput(bool gamepad)
            {
                if (gamepad)
                    _textInputGp = !_textInputGp;
                else
                    _textInputKb = !_textInputKb;
            }
            bool getTextInput(bool gamepad)
            {
                if (gamepad)
                    return (_textInputGp);
                return (_textInputKb);
            }
            void setLoadStr(bool gamepad, const std::string &str)
            {
                if (gamepad)
                    _loadGp = std::string("./inputs/").append(str).append(".input");
                else
                    _loadKb = std::string("./inputs/").append(str).append(".input");
            }
            std::string &getLoadStr(bool gamepad)
            {
                if (gamepad)
                    return (_loadGp);
                return (_loadKb);
            }
        protected:
        private:
    };
}
