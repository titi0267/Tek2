/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD06-timothe.coniel
** File description:
** convert_temp
*/

#include <iostream>
#include <iomanip>

int main(void)
{
    double temp;
    std::string type;
    double cels;
    double fahr;

    std::cin >> temp >> type;
    if (type == "Celsius") {
        fahr = (temp * 9/5) + 32;
        std::cout << std::setw(16) << std::setprecision(3) << std::fixed
                << fahr << std::setw(16) << "Fahrenheit" << std::endl;
    } else if (type == "Fahrenheit") {
        cels = 5.0 / 9.0 * (temp-32);
        std::cout << std::setw(16) << std::setprecision(3) << std::fixed
                << cels << std::setw(16) << "Celsius" << std::endl;
    }
}