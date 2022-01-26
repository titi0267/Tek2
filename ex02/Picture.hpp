/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD11-timothe.coniel
** File description:
** Picture
*/

#include <iostream>
#ifndef PICTURE_HPP_
#define PICTURE_HPP_

class Picture {
    public:
        Picture();
        Picture(const std::string &file);
        ~Picture();
        bool getPictureFromFile(const std::string &file);
        std::string data;

    protected:
    private:
};

#endif /* !PICTURE_HPP_ */
