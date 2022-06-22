/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Sound
*/

#pragma once

#include <string>
#include "headers/raylib.h"

namespace raylib {
    using RaylibSound = ::Sound;

    struct SoundRef {
        char sound[255];
        int size;

        SoundRef(const std::string &sound = "")
        {
            this->sound[(size = sound.copy(this->sound, 255))] = 0;
        }

        std::string toStr()
        {
            return std::string(sound, size);
        }
    };

    class Sound {
        bool _created;
        bool _music;
        RaylibSound _sound;

        public:
        Sound(const std::string &filename, bool music) :
            _created(true), _sound(LoadSound(filename.c_str())), _music(music) {};
        ~Sound() { if (_created) UnloadSound(_sound); };
        Sound(Sound&) = delete;
        Sound(Sound &&other)
            : _created(other._created), _sound(other._sound), _music(other._music) {other._created = false;};

        void setSoundVolume(float volume) { if (volume <= 1.0 && volume >= 0.0) SetSoundVolume(_sound, volume); };
        bool isMusic() { return (_music); };
        bool isCreated() {  return (_created); };
        void playSound() { PlaySound(_sound); };
        void stopSound() { StopSound(_sound); };
        void pauseSound() { PauseSound(_sound); };
        void resumeSound() { ResumeSound(_sound); };
        bool isSoundPlaying() { return (IsSoundPlaying(_sound)); };
    };
}
