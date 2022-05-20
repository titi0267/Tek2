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

IPizza::PizzaType Utils::getTypeFromStr(std::string type)
{
    if (type.compare("margarita") == 0)
        return (IPizza::PizzaType::Margarita);
    if (type.compare("regina") == 0)
        return (IPizza::PizzaType::Regina);
    if (type.compare("americana") == 0)
        return (IPizza::PizzaType::Americana);
    return (IPizza::PizzaType::Fantasia);
}

IPizza::PizzaSize Utils::getSizeFromStr(std::string size)
{
    if (size.compare("S") == 0)
        return (IPizza::PizzaSize::S);
    if (size.compare("M") == 0)
        return (IPizza::PizzaSize::M);
    if (size.compare("L") == 0)
        return (IPizza::PizzaSize::L);
    if (size.compare("XL") == 0)
        return (IPizza::PizzaSize::XL);
    return (IPizza::PizzaSize::XXL);
}
