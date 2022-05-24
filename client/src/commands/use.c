/*
** EPITECH PROJECT, 2022
** teams
** File description:
** use
*/

#include "../../include/teams.h"
#include "../../include/command.h"

int check_args_thread(char *buff, int thread_uuid_len)
{
    int max_sz = 0;

    if (check_is_arg(buff + thread_uuid_len) == CMD_ERROR &&
        buff[thread_uuid_len] != '\n')
        return (CMD_ERROR);
    if (buff[thread_uuid_len] == '\n')
        return (0);
    for (thread_uuid_len += 2; buff[thread_uuid_len] != '"';
        thread_uuid_len++, max_sz++) {
        if (buff[thread_uuid_len] < 48 || buff[thread_uuid_len] > 57 ||
            max_sz >= MAX_NAME_LENGTH)
            return (CMD_ERROR);
    }
    if (max_sz == 0 || buff[thread_uuid_len + 1] != '\n')
        return (CMD_ERROR);
    return (0);
}

int check_args_channel(char *buff, int channel_uuid_len)
{
    int thread_uuid_len = 0;
    int max_sz = 0;

    if (check_is_arg(buff + channel_uuid_len) == CMD_ERROR &&
        buff[channel_uuid_len] != '\n')
        return (CMD_ERROR);
    if (buff[channel_uuid_len] == '\n')
        return (0);
    for (channel_uuid_len += 2; buff[channel_uuid_len] != '"';
        channel_uuid_len++, max_sz++) {
        if (buff[channel_uuid_len] < 48 || buff[channel_uuid_len] > 57 ||
            max_sz >= MAX_NAME_LENGTH)
            return (CMD_ERROR);
    }
    thread_uuid_len = channel_uuid_len + 1;
    if (max_sz == 0 || check_args_thread(buff, thread_uuid_len) == CMD_ERROR)
        return (CMD_ERROR);
    return (0);
}

int check_full_use_command(char *buff)
{
    int team_uuid_len = 0;
    int channel_uuid_len = 0;
    int max_sz = 0;

    if (check_is_arg(buff) == CMD_ERROR)
        return (CMD_ERROR);
    for (team_uuid_len = 2; buff[team_uuid_len] != '"';
        team_uuid_len++, max_sz++) {
        if (buff[team_uuid_len] < 48 || buff[team_uuid_len] > 57 ||
            max_sz >= MAX_NAME_LENGTH)
            return (CMD_ERROR);
    }
    channel_uuid_len = team_uuid_len + 1;
    if (max_sz == 0 || check_args_channel(buff, channel_uuid_len) == CMD_ERROR)
        return (CMD_ERROR);
    return (0);
}

int c_use(char *buff, client_t *client)
{
    if (buff[0] != '\n' && check_full_use_command(buff) == CMD_ERROR)
        return (CMD_ERROR);
    printf("use\n");
    return (USE);
}