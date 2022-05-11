/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Utils
*/

#include "Utils.hpp"

Utils::Utils()
{
}

Utils::~Utils()
{
}

bool Utils::is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();

    for (;it != s.end() && std::isdigit(*it); ++it);
    return !s.empty() && it == s.end();
}
