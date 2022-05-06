/*
** EPITECH PROJECT, 2022
** teams
** File description:
** command
*/

#pragma once

enum command_nbr {
    LOGIN
};

typedef struct message_s {
    enum command_nbr command;
} message_t;
