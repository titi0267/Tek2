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
        typedef enum {
            UP,
            DOWN,
            LEFT,
            RIGHT,
            PLACE
        } Binding;
        virtual ~IBind() = default;
        virtual std::string getKeyText(Binding bind) = 0;
        virtual std::string getKeyString(Binding bind) = 0;
        virtual int getKey(Binding bind) = 0;
        virtual void setKey(Binding bind, int keyInt) = 0;
        virtual int stringToKey(const std::string &str) = 0;
        virtual std::string keyToString(int keyInt) = 0;
        virtual std::string keyToGameTxt(int keyInt) = 0;
    protected:
    private:
};
