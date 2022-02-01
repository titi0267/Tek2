/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGRUSH3-elliot.waldvogel
** File description:
** ncurses
*/

#include "ncurses.hpp"

void printBox(char *title, char *to_print, int high)
{
    int begin = high;

    mvprintw(begin, (COLS / 2), "##");
    mvprintw(begin, (COLS / 2) + 3, title);
    mvprintw(begin, (COLS / 2) + 3 + strlen(title), " ");
    mvprintw(begin, (COLS / 2) + 4 + strlen(title), std::string(25 - strlen(title), '#').c_str());
    mvprintw(begin + 1, (COLS / 2), "#                           #");
    mvprintw(begin + 2, (COLS / 2), "#");
    mvprintw(begin + 2, (COLS / 2) + 1, std::string(14 - (strlen(to_print) / 2), ' ').c_str());
    mvprintw(begin + 2, (COLS / 2) + (14 - (strlen(to_print) / 2)), to_print);
    mvprintw(begin + 2, (COLS / 2) + 28, "#");
    mvprintw(begin + 3, (COLS / 2), "#                           #");
    mvprintw(begin + 4, (COLS / 2), "#############################");
}

int loop()
{
    Get_file info;
    int y = 0;
    int x = 0;
    char *tmp;
    int line = 0;

    initscr();
    keypad(stdscr, TRUE);
    curs_set(0);

    while (1) {
        clear();
        getmaxyx(stdscr, y, x);
        printBox((char*)"Time", (char *)info.getTime().c_str(), (LINES / 2) + line);
        line += 6;
        printBox((char*)"Username", (char *)info.getUsername().c_str(), (LINES / 2) + line);
        line += 6;
        printBox((char*)"Hostname", (char *)info.getHostname().c_str(), (LINES / 2) + line);
        info.updateTime();
        line = 0;
        refresh();
        sleep(1);
    }

    refresh();
    return (0);
}

int ncursesMain()
{
    loop();
    return (0);
}