/*
** EPITECH PROJECT, 2022
** teams
** File description:
** print_struct
*/

#include "../../include/teams.h"
#include <dlfcn.h>

void get_all_functions(logging_t *logging, void *logging_handler)
{
    logging->server_event_channel_created =
    dlsym(logging_handler, "server_event_channel_created");
    logging->server_event_private_message_sended =
    dlsym(logging_handler, "server_event_private_message_sended");
    logging->server_event_reply_created =
    dlsym(logging_handler, "server_event_reply_created");
    logging->server_event_team_created =
    dlsym(logging_handler, "server_event_team_created");
    logging->server_event_thread_created =
    dlsym(logging_handler, "server_event_thread_created");
    logging->server_event_user_created =
    dlsym(logging_handler, "server_event_user_created");
    logging->server_event_user_loaded =
    dlsym(logging_handler, "server_event_user_loaded");
    logging->server_event_user_logged_in =
    dlsym(logging_handler, "server_event_user_logged_in");
    logging->server_event_user_logged_out =
    dlsym(logging_handler, "server_event_user_logged_out");
    logging->server_event_user_subscribed =
    dlsym(logging_handler, "server_event_user_subscribed");
}

logging_t *create_struct()
{
    logging_t *logging = malloc(sizeof(logging_t));
    char *error = NULL;

    if (logging == NULL)
        return (NULL);
    void *logging_handler = dlopen("./print_lib/libmyteams.so", RTLD_LAZY);
    if ((error = dlerror()) != NULL) {
        free(logging);
        return (NULL);
    }
    get_all_functions(logging, logging_handler);
    return (logging);
}