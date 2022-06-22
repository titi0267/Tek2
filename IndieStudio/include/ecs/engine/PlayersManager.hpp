/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** PlayersManager
*/

#pragma once

#include <deque>
#include <cstdint>
#include <stdexcept>
#include <unordered_map>
#include "ecs/engine/PlayerId.hpp"
#include "ecs/engine/Network.hpp"

namespace ecs {
    class PlayersManager {
        using ConnId = network::ConnId;

        bool _acceptNewPlayers = true;
        int _maxPlayers;
        std::deque<PlayerId> _availaibleIds;
        std::unordered_map<ConnId, std::vector<PlayerId>> _connToPlayers;

        public:
        PlayersManager(int maxPlayers);

        bool canAcceptPlayers(int nbPlayers);
        void stopAcceptingPlayers();
        void acceptNewPlayers();
        PlayerId reservePlayerId(ConnId conn);
        void clientDisconnect(ConnId conn);
        std::vector<PlayerId> getPlayersOfConn(ConnId conn);
        std::vector<PlayerId> getAssignedIds()
        {
            std::vector<PlayerId> ids;

            for (auto &[conn, assigned] : _connToPlayers) {
                for (PlayerId id : assigned)
                    ids.push_back(id);
            }
            return ids;
        };

        bool isIdAvailaible();
        PlayerId reserveNextPlayerId();
        void unreservePlayerId(PlayerId id);
        bool isIdUnassigned(PlayerId id);
    };
}
