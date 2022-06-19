/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** PlayersManager
*/

#include "ecs/engine/PlayersManager.hpp"

ecs::PlayersManager::PlayersManager(int maxPlayers) : _maxPlayers(maxPlayers)
{
    for (int i = 0; i < _maxPlayers; i++)
        _availaibleIds.push_back(i);
}

bool ecs::PlayersManager::canAcceptPlayers(int nbPlayers)
{
    return _acceptNewPlayers && _availaibleIds.size() >= nbPlayers;
}

void ecs::PlayersManager::stopAcceptingPlayers()
{
    _acceptNewPlayers = false;
}

void ecs::PlayersManager::acceptNewPlayers()
{
    _acceptNewPlayers = true;
}

ecs::PlayerId ecs::PlayersManager::reservePlayerId(ConnId conn)
{
    PlayerId id;

    if (_availaibleIds.size() == 0)
        throw std::runtime_error("Could not attribute player id");
    id = _availaibleIds.front();
    _availaibleIds.pop_front();
    if (_connToPlayers.find(conn) != _connToPlayers.end())
        _connToPlayers[conn].push_back(id);
    else
        _connToPlayers.insert({conn, {id}});
    std::cout << "Assigned Player #" << id << " to conn #" << conn << std::endl;
    return id;
}

void ecs::PlayersManager::clientDisconnect(ConnId conn)
{
    if (_connToPlayers.find(conn) == _connToPlayers.end())
        return;

    auto &ids = _connToPlayers[conn];

    for (int i = ids.size() - 1; i >= 0; i--) {
        _availaibleIds.push_front(ids[i]);
        std::cout << "Unassigned Player ID #" << ids[i] << std::endl;
    }
    _connToPlayers.erase(conn);
}

std::vector<ecs::PlayerId> ecs::PlayersManager::getPlayersOfConn(ConnId conn)
{
    if (_connToPlayers.find(conn) == _connToPlayers.end())
        return {};
    return _connToPlayers[conn];
}

bool ecs::PlayersManager::isIdAvailaible()
{
    return _availaibleIds.size() > 0;
}

 ecs::PlayerId ecs::PlayersManager::reserveNextPlayerId()
{
    PlayerId id = _availaibleIds.front();

    _availaibleIds.pop_front();
    return id;
}

void ecs::PlayersManager::unreservePlayerId(PlayerId id)
{
    _availaibleIds.push_back(id);
}

bool ecs::PlayersManager::isIdUnassigned(PlayerId id)
{
    return std::find(_availaibleIds.begin(), _availaibleIds.end(), id) != _availaibleIds.end();
}
