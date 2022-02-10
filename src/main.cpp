/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** main
*/

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>

std::string getStrFromFile(const std::string &file)
{
    char element;
    std::string str = "";
    std::ifstream myfile(file, std::ios::in);

    if (!myfile.fail()) {
        while (myfile.get(element))
            str += element;
    } else {
        const char *s = "ERROR";
        std::string str(s);
        str = s;
        return str;
    }
    return str;
}

std::vector<std::string> split(std::string to_split, char token)
{
    std::stringstream streamData(to_split);
    std::vector<std::string> outputArray;
    std::string val;

    while (std::getline(streamData, val, token)) {
        outputArray.push_back(val);
    }
    return outputArray;
}

int main(int ac, char **av)
{
    if (ac != 2)
        return 84;
    std::string file = getStrFromFile(av[1]);
    std::string *array;

    if (file == "ERROR")
        return 84;
    split(file, '\n');
    return (0);
}