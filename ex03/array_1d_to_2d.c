/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD04am-timothe.coniel
** File description:
** array_1d_to_2d
*/
#include <stdlib.h>
#include <stdio.h>

void array_1d_to_2d(const int *array, size_t height, size_t width, int ***res)
{
    (*res) = malloc(sizeof(int *) * height);
    for (int i = 0; i < (int)height; i++) {
        (*res)[i] = malloc(sizeof(int) * width);
    }
    for (int i = 0; i < (int)height; i++) {
        for (int y = 0; y < (int)width; y++) {
            (*res)[i][y] = array[y];
        }
    }
}

void array_2d_free(int **array, size_t height, size_t width)
{
    for (int i = 0; i < (int)height; i++)
        free(array[i]);
    free(array);
}