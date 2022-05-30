/*
** EPITECH PROJECT, 2022
** teams
** File description:
** use
*/

#include "../../include/teams.h"
#include "../../include/command.h"

int check_args_thread(char *buff, int thread_uuid_len, client_t *client)
{
    int max_sz = 0;

    if (check_is_arg(buff + thread_uuid_len) == CMD_ERROR &&
        buff[thread_uuid_len] != '\n')
        return (CMD_ERROR);
    if (buff[thread_uuid_len] == '\n')
        return (0);
    thread_uuid_len += 2;
    for (int i = 0; buff[thread_uuid_len] != '"';
        thread_uuid_len++, max_sz++, i++) {
        client->thread_uuid[i] = buff[thread_uuid_len];
        if (buff[thread_uuid_len] < 48 || buff[thread_uuid_len] > 57 ||
            max_sz >= MAX_NAME_LENGTH)
            return (CMD_ERROR);
    }
    if (max_sz == 0 || buff[thread_uuid_len + 1] != '\n')
        return (CMD_ERROR);
    return (0);
}

int check_args_channel(char *buff, int channel_uuid_len, client_t *cli)
{
    int thd_uuid_ln = 0;
    int max_sz = 0;

    if (check_is_arg(buff + channel_uuid_len) == CMD_ERROR &&
        buff[channel_uuid_len] != '\n')
        return (CMD_ERROR);
    if (buff[channel_uuid_len] == '\n')
        return (0);
    channel_uuid_len += 2;
    for (int i = 0; buff[channel_uuid_len] != '"';
        channel_uuid_len++, max_sz++, i++) {
        cli->channel_uuid[i] = buff[channel_uuid_len];
        if (buff[channel_uuid_len] < 48 || buff[channel_uuid_len] > 57 ||
            max_sz >= MAX_NAME_LENGTH)
            return (CMD_ERROR);
    }
    thd_uuid_ln = channel_uuid_len + 1;
    if (max_sz == 0 || check_args_thread(buff, thd_uuid_ln, cli) == CMD_ERROR)
        return (CMD_ERROR);
    return (0);
}

int check_full_use_command(char *buff, client_t *cli)
{
    int team_uuid_len = 2;
    int chnl_uuid_ln = 0;
    int max_sz = 0;

    if (check_is_arg(buff) == CMD_ERROR)
        return (CMD_ERROR);
    for (int i = 0; buff[team_uuid_len] != '"';
        team_uuid_len++, max_sz++, i++) {
        cli->team_uuid[i] = buff[team_uuid_len];
        if (buff[team_uuid_len] < 48 || buff[team_uuid_len] > 57 ||
            max_sz >= MAX_NAME_LENGTH)
            return (CMD_ERROR);
    }
    chnl_uuid_ln = team_uuid_len + 1;
    if (max_sz == 0 || check_args_channel(buff, chnl_uuid_ln, cli) == CMD_ERROR)
        return (CMD_ERROR);
    return (0);
}

int c_use(char *buff, client_t *client)
{
    client->use_status = DEFAULT;
    memset(client->team_uuid, 0, sizeof(MAX_NAME_LENGTH));
    memset(client->channel_uuid, 0, sizeof(MAX_NAME_LENGTH));
    memset(client->thread_uuid, 0, sizeof(MAX_NAME_LENGTH));
    if (buff[0] != '\n' && check_full_use_command(buff, client) == CMD_ERROR)
        return (CMD_ERROR);
    if (strlen(client->team_uuid) == 0)
        client->use_status = DEFAULT;
    if (strlen(client->team_uuid) != 0)
        client->use_status = TEAMS;
    if (strlen(client->channel_uuid) != 0)
        client->use_status = CHANNEL;
    if (strlen(client->thread_uuid) != 0)
        client->use_status = THREADS;
    printf("use : ");
    printf("team ?: %s | channel ?: %s | thread ?: %s\n", client->team_uuid,
        client->channel_uuid, client->thread_uuid);
    return (USE);
}