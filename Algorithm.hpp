/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD12-timothe.coniel
** File description:
** Algorithm
*/

#include <iostream>
#ifndef ALGORITHM_HPP_
#define ALGORITHM_HPP_

template<typename T>
void swap(T &a, T &b)
{
    T c = a;
    a = b;
    b = c;
}

template<typename T>
T min(T a, T b)
{
    if (a <= b)
        return a;
    return b;
}

template<typename T>
T max(T a, T b)
{
    if (a >= b)
        return a;
    return b;
}

template<typename T>
T clamp(T value, T a, T b)
{
    if (a <= b && a <= value) {
        if (b > value)
            return value;
        else
            return b;
    } else if (b <= value && b <= a) {
        if (a > value)
            return value;
        else
            return a;
    } //else if (value <= a && value <= b) {
    if (a > b)
        return b;
    return a;
}

#endif /* !ALGORITHM_HPP_ */
