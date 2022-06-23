/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD11-timothe.coniel
** File description:
** Picture
*/

#include "Picture.hpp"
#include <fstream>

Picture::Picture(const std::string &file)
{
    getPictureFromFile(file);
}

Picture::Picture()
{
    data = "";
}

Picture::~Picture()
{
}

bool Picture::getPictureFromFile(const std::string &file)
{
    if (file == "") {
        data = "";
        return true;
    }
    std::ifstream buff (file, std::ios::in);

    if (!buff) {
        data = "ERROR";
        return false;
    }
    else {
        std::string str((std::istreambuf_iterator<char>(buff)),(std::istreambuf_iterator<char>()));
        data = str;
        buff.close();
    }
    return true;
}