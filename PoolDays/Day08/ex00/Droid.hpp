/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD08-timothe.coniel
** File description:
** Droid
*/

#include <iostream>
#ifndef DRIOD_HPP_
#define DRIOD_HPP_

class Droid {
    public:
                Droid(std::string serial = "");
                Droid(Droid& copy);
                ~Droid();
        void         setId(std::string serial);
        std::string  getId();
        void         setEnergy(size_t Energy);
        size_t       getEnergy();
        const size_t getAttack();
        const size_t getToughness();
        void         setStatus(std::string *stat);
        std::string *getStatus();
        void         operator=(Droid &other);
        bool         operator==(Droid &other);
        bool         operator!=(Droid &other);
        Droid&       operator<<(size_t &energy);

    protected:
    private:
        std::string _Id;
        size_t _Energy;
        const size_t _Attack = 25;
        const size_t _Toughness = 15;
        std::string *_Status;
};

std::ostream &operator<<(std::ostream &os, Droid &other);

#endif /* !DRIOD_HPP_ */
