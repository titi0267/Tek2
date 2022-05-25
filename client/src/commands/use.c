/*
** EPITECH PROJECT, 2022
** teams
** File description:
** use
*/

#include "../../include/teams.h"
#include "../../include/command.h"

int check_args_thread(char *buff, int thread_uuid_len, cli_use_t *use)
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
        use->thread_uuid[i] = buff[thread_uuid_len];
        if (buff[thread_uuid_len] < 48 || buff[thread_uuid_len] > 57 ||
            max_sz >= MAX_NAME_LENGTH)
            return (CMD_ERROR);
    }
    if (max_sz == 0 || buff[thread_uuid_len + 1] != '\n')
        return (CMD_ERROR);
    return (0);
}

int check_args_channel(char *buff, int channel_uuid_len, cli_use_t *use)
{
    int thread_uuid_len = 0;
    int max_sz = 0;

    if (check_is_arg(buff + channel_uuid_len) == CMD_ERROR &&
        buff[channel_uuid_len] != '\n')
        return (CMD_ERROR);
    if (buff[channel_uuid_len] == '\n')
        return (0);
    channel_uuid_len += 2;
    for (int i = 0; buff[channel_uuid_len] != '"';
        channel_uuid_len++, max_sz++, i++) {
        use->channel_uuid[i] = buff[channel_uuid_len];
        if (buff[channel_uuid_len] < 48 || buff[channel_uuid_len] > 57 ||
            max_sz >= MAX_NAME_LENGTH)
            return (CMD_ERROR);
    }
    thread_uuid_len = channel_uuid_len + 1;
    if (max_sz == 0 || check_args_thread(buff, thread_uuid_len, use) == CMD_ERROR)
        return (CMD_ERROR);
    return (0);
}

int check_full_use_command(char *buff, cli_use_t *use)
{
    int team_uuid_len = 2;
    int channel_uuid_len = 0;
    int max_sz = 0;

    memset(use->team_uuid, 0, MAX_NAME_LENGTH);
    memset(use->channel_uuid, 0, MAX_NAME_LENGTH);
    memset(use->thread_uuid, 0, MAX_NAME_LENGTH);
    if (check_is_arg(buff) == CMD_ERROR)
        return (CMD_ERROR);
    for (int i = 0; buff[team_uuid_len] != '"';
        team_uuid_len++, max_sz++, i++) {
        use->team_uuid[i] = buff[team_uuid_len];
        if (buff[team_uuid_len] < 48 || buff[team_uuid_len] > 57 ||
            max_sz >= MAX_NAME_LENGTH)
            return (CMD_ERROR);
    }
    channel_uuid_len = team_uuid_len + 1;
    if (max_sz == 0 || check_args_channel(buff, channel_uuid_len, use) == CMD_ERROR)
        return (CMD_ERROR);
    return (0);
}

int c_use(char *buff, client_t *client)
{
    message_t msg;
    cli_use_t *use = malloc(sizeof(cli_use_t));

    use->team_uuid[0] = '\0';
    use->channel_uuid[0] = '\0';
    use->thread_uuid[0] = '\0';
    if (buff[0] != '\n' && check_full_use_command(buff, use) == CMD_ERROR) {
        free(use);
        return (CMD_ERROR);
    }
    msg.command = USE;
    write(client->socket_fd, &msg, sizeof(message_t));
    printf("use : ");
    printf("team ?: %s | channel ?: %s | thread ?: %s\n", use->team_uuid,
        use->channel_uuid, use->thread_uuid);
    write(client->socket_fd, use, sizeof(cli_use_t));
    free(use);
    return (USE);
}