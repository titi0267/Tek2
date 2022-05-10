/*
** EPITECH PROJECT, 2022
** plaza
** File description:
** IMutex
*/

#pragma once

class IMutex {
    public :
        virtual ~IMutex () = default ;
        virtual void lock () = 0;
        virtual void unlock () = 0;
        virtual int trylock () = 0;
};
