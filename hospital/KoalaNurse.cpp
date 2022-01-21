/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD06-timothe.coniel
** File description:
** KoalaNurse
*/

#include "KoalaNurse.hpp"
#include <fstream>
#include <sstream>

KoalaNurse::KoalaNurse(int num_id)
{
    id = num_id;
}

KoalaNurse::~KoalaNurse()
{
    std::cout << "Nurse " << id << ": Finally some rest!" << std::endl;
}

void KoalaNurse::giveDrug(std::string str, SickKoala *s_koala)
{
    s_koala->takeDrug(str);
}

std::string KoalaNurse::readReport(std::string str)
{
    std::string name;
    std::string drug;
    std::ostringstream out;

    name = str.substr(0, str.find("."));
    std::ifstream file (str, std::ios::in);

    if (!file)
        return ("");
    out << file.rdbuf();
    drug = out.str();
    file.close();
    std::cout << "Nurse " << id << ": Kreog! Mr." << name << " needs a " << drug << "!" << std::endl;
    return (drug);
}

void KoalaNurse::timeCheck(void)
{
    if (working == false) {
        std::cout << "Nurse " << id << ": Time to get to work!" << std::endl;
        working = true;
    } else {
        std::cout << "Nurse " << id << ": Time to go home to my eucalyptus forest!" << std::endl;
        working = false;
    }
}
