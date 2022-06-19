/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** SoundManager
*/

#pragma once

#include <unordered_map>
#include <stdexcept>
#include "Sound.hpp"

namespace raylib {
    class SoundManager {
        std::unordered_map<std::string, Sound> _sounds;
        bool _music;
        bool _sound;
        float _musicVolume;
        float _soundVolume;
        public:
        SoundManager() : _music(true), _sound(true), _musicVolume(1), _soundVolume(1)
        {
            InitAudioDevice();
        }

        ~SoundManager()
        {
            CloseAudioDevice();
        }

        Sound &loadSound(const std::string &id, const std::string &path, bool music)
        {
            if (_sounds.find(id) != _sounds.end())
                throw std::runtime_error("Sound " + id + " already used");
            _sounds.insert({id, Sound(path, music)});
            return (_sounds.at(id));
        }
        Sound &getSound(const std::string &id)
        {
            if (_sounds.find(id) == _sounds.end())
                throw std::runtime_error("Sound " + id + " does not exist");
            return (_sounds.at(id));
        }
        void setMusicVolume()
        {
            for (auto it = _sounds.begin(); it != _sounds.end(); it++) {
                raylib::Sound &sound = it->second;
                if (!sound.isMusic())
                    continue;
                if (!_music)
                    sound.setSoundVolume(0);
                else
                    sound.setSoundVolume(_musicVolume);
            }
        }
        void setSoundVolume()
        {
            for (auto it = _sounds.begin(); it != _sounds.end(); it++) {
                raylib::Sound &sound = it->second;
                if (sound.isMusic())
                    continue;
                if (!_sound)
                    sound.setSoundVolume(0);
                else
                    sound.setSoundVolume(_soundVolume);
            }
        }
        void toggleMusic()
        {
            _music = !_music;
        }
        void toggleSound()
        {
            _sound = !_sound;
        }
    };
}