/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD04am-timothe.coniel
** File description:
** pyramid
*/
#include <stdio.h>
#include <stdlib.h>

int check_lower(const unsigned int **map, unsigned int i, int index)
{
    if (map[i+1][index] <= map[i+1][index +1]) {
        return (0);
    } else {
        return (1);
    }
}

int pyramid_path(unsigned int size, const unsigned int **map)
{
    int path = 0;
    int index = 0;

    for (unsigned int i = 0; i <= size; i++) {
        if (check_lower(map, i, index) == 0) {
            path += map[i][index];
        }
        else {
            path += map[i][index+1];
            index += 1;
        }
    }
    return (path);
}
