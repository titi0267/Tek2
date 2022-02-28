/*
** EPITECH PROJECT, 2022
** $
** File description:
** utils
*/

#include "nano.hpp"

bool isValidComponent(std::string value)
{
    std::string components[] = {"4001", "4011", "4030", "4071", "4081", "4069", "4008", "4013", "4017", "4040", "4094", "4512", "4514", "4801", "2716"};
    for (int i = 0; i < 15; i++) {
        if (value == components[i])
            return true;
    }
    return false;
}

bool isInChipsets(std::tuple<std::string, std::string> *chipsets, std::string link)
{
    std::string tmp = "a";

    for (int i = 0; tmp != ""; i++) {
        tmp = std::get<1>(chipsets[i]);
        if (tmp == link)
            return true;
    }
    return false;
}

int get_space(std::string str, int value)
{
    int i = value;
    int j = 0;

    for (; str[i + 1] == ' '; i++)
        j++;

    return j;
}

std::string removeNewLine(std::string str)
{
    std::string newStr(str.length(), '\0');
    std::string::size_type i = 0;
    int j = 0;

    for (; str[i] == '\n'; i++);
    for (; i < str.size(); i++) {
        for (; str[i + 1] && str[i] ==  '\n' && str[i + 1] == '\n'; i++);
        newStr[j] = str[i];
        if (str[i] == '\n' && str[i + 1] && str[i + 1] == ' ')
            i += get_space(str, i);
        j++;
    }
    return (newStr);
}

std::string removeComments(std::string str)
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

std::tuple<std::string, std::string, std::string, std::string> *getLinks(std::vector<std::string> splitedFile)
{
    int matchLen = 0;
    int i = 0;

    std::regex rgx("(\\w+):([0-9]+)[ \t]+(\\w+):([0-9]+)");
    std::sregex_iterator iter(splitedFile[2].begin(), splitedFile[2].end(), rgx);
    std::sregex_iterator other_iter(splitedFile[2].begin(), splitedFile[2].end(), rgx);
    std::sregex_iterator end;

    while (iter != end) {
        matchLen++;
        ++iter;
    }
    std::tuple <std::string, std::string, std::string, std::string> *links = new std::tuple <std::string, std::string, std::string, std::string>[matchLen + 1];
    while (other_iter != end) {
        links[i] = std::make_tuple((*other_iter)[1], (*other_iter)[2], (*other_iter)[3], (*other_iter)[4]);
        i++;
        ++other_iter;
    }
    links[i] = std::make_tuple("", "", "", "");

    return links;
}

std::tuple<std::string, std::string> *getChipset(std::vector<std::string> splitedFile)
{
    int matchLen = 0;
    int i = 0;

    std::regex rgx("(\\w+) (\\w+)");
    std::sregex_iterator iter(splitedFile[1].begin(), splitedFile[1].end(), rgx);
    std::sregex_iterator other_iter(splitedFile[1].begin(), splitedFile[1].end(), rgx);
    std::sregex_iterator end;

    while (iter != end) {
        matchLen++;
        ++iter;
    }
    std::tuple <std::string, std::string> *chipset = new std::tuple <std::string, std::string>[matchLen + 1];
    while (other_iter != end) {
        chipset[i] = std::make_tuple((*other_iter)[1], (*other_iter)[2]);
        i++;
        ++other_iter;
    }
    chipset[i] = std::make_tuple("", "");

    return chipset;
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
