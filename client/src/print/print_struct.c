/*
** EPITECH PROJECT, 2022
** teams
** File description:
** print_struct
*/

/*
** EPITECH PROJECT, 2022
** teams
** File description:
** print_struct
*/

#include "../../include/teams.h"
#include <dlfcn.h>

void get_all_functions_last(logging_t *logging, void *logging_handler)
{
    logging->client_print_user =
    dlsym(logging_handler, "client_print_user");
    logging->client_print_users =
    dlsym(logging_handler, "client_print_users");
    logging->client_private_message_print_messages =
    dlsym(logging_handler, "client_private_message_print_messages");
    logging->client_team_print_channels =
    dlsym(logging_handler, "client_team_print_channels");
    logging->client_thread_print_replies =
    dlsym(logging_handler, "client_thread_print_replies");
}

void get_all_functions_next_next(logging_t *logging, void *logging_handler)
{
    logging->client_print_team =
    dlsym(logging_handler, "client_print_team");
    logging->client_print_team_created =
    dlsym(logging_handler, "client_print_team_created");
    logging->client_print_teams =
    dlsym(logging_handler, "client_print_teams");
    logging->client_print_thread =
    dlsym(logging_handler, "cclient_print_thread");
    logging->client_print_thread_created =
    dlsym(logging_handler, "client_print_thread_created");
    logging->client_print_unsubscribed =
    dlsym(logging_handler, "client_print_unsubscribed");
    get_all_functions_last(logging, logging_handler);
}

void get_all_functions_next(logging_t *logging, void *logging_handler)
{
    logging->client_event_logged_out =
    dlsym(logging_handler, "client_event_logged_out");
    logging->client_event_private_message_received =
    dlsym(logging_handler, "client_event_private_message_received");
    logging->client_event_team_created =
    dlsym(logging_handler, "client_event_team_created");
    logging->client_event_thread_created =
    dlsym(logging_handler, "client_event_thread_created");
    logging->client_event_thread_reply_received =
    dlsym(logging_handler, "client_event_thread_reply_received");
    logging->client_print_channel =
    dlsym(logging_handler, "client_print_channel");
    logging->client_print_channel_created =
    dlsym(logging_handler, "client_print_channel_created");
    logging->client_print_reply_created =
    dlsym(logging_handler, "client_print_reply_created");
    logging->client_print_subscribed =
    dlsym(logging_handler, "client_print_subscribed");
    get_all_functions_next_next(logging, logging_handler);
}

void get_all_functions(logging_t *logging, void *logging_handler)
{
    logging->client_channel_print_threads =
    dlsym(logging_handler, "client_channel_print_threads");
    logging->client_error_already_exist =
    dlsym(logging_handler, "client_error_already_exist");
    logging->client_error_unauthorized =
    dlsym(logging_handler, "client_error_unauthorized");
    logging->client_error_unknown_channel =
    dlsym(logging_handler, "client_error_unknown_channel");
    logging->client_error_unknown_team =
    dlsym(logging_handler, "client_error_unknown_team");
    logging->client_error_unknown_thread =
    dlsym(logging_handler, "client_error_unknown_thread");
    logging->client_error_unknown_user =
    dlsym(logging_handler, "client_error_unknown_user");
    logging->client_event_channel_created =
    dlsym(logging_handler, "client_event_channel_created");
    logging->client_event_logged_in =
    dlsym(logging_handler, "client_event_logged_in");
    get_all_functions_next(logging, logging_handler);
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