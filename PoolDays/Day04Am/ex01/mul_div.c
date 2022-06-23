/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD04am-timothe.coniel
** File description:
** mul_div
*/
#include <stdio.h>

void mul_div_long(int a, int b, int *mul, int *div)
{
    *mul = a * b;
    if (b != 0)
        *div = a / b;
    else
        *div = 42;
}

void mul_div_short(int *a, int *b)
{
    int tmp_a = *a;
    int tmp_b = *b;

    *a = tmp_a * tmp_b;
    if (tmp_b != 0)
        *b = tmp_a / tmp_b;
    else
        *b = 42;
}
