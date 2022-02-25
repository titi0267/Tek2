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

std::vector<std::string> getGoodFile(char **av)
{
    std::regex rgx(".chipsets:\n((input|output|\\d{4}|clock|true|false)([ \t]+)\\w+\n)+.links:\n(\\w+:\\w+([ \t]+)\\w+:\\w+(\n|))+");
    std::string file = getStrFromFile(av[1]);
    if (file == "ERROR")
        exit(84);
    std::string unCommentedFile = removeComments(file);
    std::string noNewLineFile = removeNewLine(unCommentedFile);
    std::string str = strdup(noNewLineFile.c_str());

    if (std::regex_match(str, rgx))
        std::cout << "match" << std::endl;
    else {
        std::cout << "match pas" << std::endl;
        exit (84);
    }
    std::vector<std::string>  splitedFile = split(str, '.');

    return splitedFile;
}

int main(int ac, char **av)
{
    if (ac != 2)
        return 84;
    std::vector<std::string> splitedFile = getGoodFile(av);
    std::string input;
    Chipsets *chipsets = new Chipsets(av);
    std::tuple<std::string, std::string> *chipset = getChipset(splitedFile);
    std::tuple<std::string, std::string, std::string, std::string> *links = getLinks(splitedFile);
    // while (1) {
    //     std::cout << "> ";
    //     std::cin >> input;
    //     handleCommand(input);
    // }
    return (0);
}