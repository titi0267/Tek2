/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** main
*/

#include "nano.hpp"

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

void handleCommand(std::string cmd)
{
    if (cmd == "exit")
        exit(0);
}

int main(int ac, char **av)
{
    if (ac != 2)
        return 84;
    std::string file = getStrFromFile(av[1]);
    std::string unCommentedFile = removeComments(file);
    std::string input;
    std::vector<std::string>  splitedFile = split(unCommentedFile, '.');
    std::tuple<std::string, std::string> *chipset = getChipset(splitedFile);
    std::tuple<std::string, std::string, std::string, std::string> *links = getLinks(splitedFile);
    if (file == "ERROR")
        return 84;
    
    // while (1) {
    //     std::cout << "> ";
    //     std::cin >> input;
    //     handleCommand(input);
    // }
    return (0);
}