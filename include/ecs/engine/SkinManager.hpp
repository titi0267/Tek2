/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** SkinManager
*/

#pragma once

#include <deque>
#include <string>
#include <unordered_map>
#include "ecs/engine/PlayerId.hpp"

namespace ecs {
    class SkinManager {
        std::deque<std::string> _availaibleSkins;
        std::unordered_map<PlayerId, std::string> _assignedSkins;

        public:
        SkinManager();

        const std::string &assignRandomSkin(PlayerId id);
        const std::string &assignFirstSkin(PlayerId id);
        const std::string &assignLastSkin(PlayerId id);
        void assignSkinToPlayer(const std::string &skin, PlayerId id);
        void unassignedSkin(PlayerId id, bool front);
        const std::string &getPlayerSkin(PlayerId id);
        bool hasSkinAssigned(PlayerId id);
    };
}
