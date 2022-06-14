/*
** EPITECH PROJECT, 2022
** input
** File description:
** IBind
*/

#pragma once

#include <string>

class IBind {
    public:
        virtual ~IBind() = default;
        virtual std::string getUpString() = 0;
        virtual std::string getDownString() = 0;
        virtual std::string getLeftString() = 0;
        virtual std::string getRightString() = 0;
        virtual std::string getPlaceString() = 0;
        virtual int stringToKey(const std::string &str) = 0;
        virtual std::string keyToString(int keyInt) = 0;
    protected:
    private:
};
