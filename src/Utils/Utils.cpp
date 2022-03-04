/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** Utils
*/

#include "Utils.hpp"

std::vector<std::string> nts::Utils::getGoodFile(char **av)
{
    std::regex rgx(".chipsets:\n((input|output|\\d{4}|clock|true|false)([ \t]+)\\w+\n)+.links:\n(\\w+:\\w+([ \t]+)\\w+:\\w+(\n|))+");
    std::string file = getStrFromFile(av[1]);
    if (file == "ERROR")
        throw Error("Cannot read file");
    std::string unCommentedFile = removeComments(file);
    std::string noNewLineFile = removeNewLine(unCommentedFile);
    std::string str(noNewLineFile.c_str());

    if (!std::regex_match(str, rgx))
        throw Error("Invalid file");
    std::vector<std::string>  splitedFile = split(str, '.');

    return splitedFile;
}

std::string nts::Utils::getStrFromFile(const std::string &file)
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

std::vector<std::string> nts::Utils::split(std::string to_split, char token)
{
    std::stringstream streamData(to_split);
    std::vector<std::string> outputArray;
    std::string val;

    while (std::getline(streamData, val, token)) {
        outputArray.push_back(val);
    }
    return outputArray;
}

int nts::Utils::get_space(std::string str, int value)
{
    int i = value;
    int j = 0;

    for (; str[i + 1] == ' '; i++)
        j++;

    return j;
}

bool nts::Utils::isValidComponent(std::string value)
{
    std::string components[] = {"4001", "4011", "4030", "4071", "4081", "4069", "4008", "4013", "4017", "4040", "4094", "4512", "4514", "4801", "2716"};
    for (int i = 0; i < 15; i++) {
        if (value == components[i])
            return true;
    }
    return false;
}

bool nts::Utils::isInChipsets(std::vector<ChipsetPair> chipsets, std::string link)
{
    auto itr = std::begin(chipsets);
    std::string tmp = "";

    for (; itr != std::end(chipsets); ++itr) {
        tmp = std::get<1>(*itr);
        if (tmp == link)
            return true;
    }
    return false;
}

std::string nts::Utils::removeComments(std::string str)
{
    std::string newStr(str.length(), '\0');
    std::string::size_type i = 0;
    int j = 0;
    bool isCommented = false;

    for (; i < str.size(); i++) {
        if (str[i] == '#')
            isCommented = true;
        for (; isCommented && i < str.size(); i++)
            isCommented = str[i] == '\n' ? false : true;
        if (!isCommented)
            newStr[j] = str[i];
        j++;
    }
    return newStr;
}

std::string nts::Utils::removeNewLine(std::string str)
{
    std::string newStr;
    std::string::size_type i = 0;
    int j = 0;

    for (; str[i] == '\n'; i++);
    for (; i < str.size(); i++) {
        for (; str[i + 1] && str[i] ==  '\n' && str[i + 1] == '\n'; i++);
        newStr.push_back(str[i]);
        if (str[i] == '\n' && str[i + 1] && str[i + 1] == ' ')
            i += get_space(str, i);
        j++;
    }
    return (newStr);
}

std::vector<LinkPairs> nts::Utils::getLinks(std::vector<std::string> splitedFile)
{
    std::regex rgx("(\\w+):([0-9]+)[ \t]+(\\w+):([0-9]+)");
    std::sregex_iterator iter(splitedFile[2].begin(), splitedFile[2].end(), rgx);
    std::vector<LinkPairs> links;
    std::sregex_iterator end;

    while (iter != end) {
        links.push_back(std::make_tuple((*iter)[1], (*iter)[2], (*iter)[3], (*iter)[4]));
        ++iter;
    }

    return links;
}

std::vector<ChipsetPair> nts::Utils::getChipset(std::vector<std::string> splitedFile)
{
    std::regex rgx("(\\w+)[ \t]+(\\w+)");
    std::sregex_iterator iter(splitedFile[1].begin(), splitedFile[1].end(), rgx);
    std::sregex_iterator end;
    std::vector<ChipsetPair> chipset;

    while (iter != end) {
        chipset.push_back(std::make_tuple((*iter)[1], (*iter)[2]));
        ++iter;
    }
    return chipset;
}
