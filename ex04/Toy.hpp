/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD11-timothe.coniel
** File description:
** Toy
*/

#include "Picture.hpp"
#include <iostream>
#ifndef TOY_HPP_
#define TOY_HPP_


class Toy : public Picture {
    public:
        Toy();
        Toy& operator=(const Toy&);
        //std::ostream& operator<<(Toy &toy);
        ~Toy();
        enum ToyType {
            BASIC_TOY,
            ALIEN,
            WOODY,
            BUZZ
        };
        Toy(ToyType type, std::string name, const std::string &file);
        int getType() const;
        std::string getName() const;
        void setName(std::string);
        bool setAscii(const std::string &file);
        std::string getAscii() const;
        virtual void speak(std::string statement);
        Toy &operator<<(std::string str);

    protected:
        ToyType _type;
        std::string _name;
        Picture _picture;
    private:
};

std::ostream &operator<<(std::ostream &os, Toy &other);

#endif /* !TOY_HPP_ */
