/*
** EPITECH PROJECT, 2022
** teams
** File description:
** help
*/

#include "../../include/teams.h"
#include "../../include/command.h"

void provide_help(void)
{
    printf("    /unsubscribe [\"team_uuid\"] : unsubscribe from a team\n");
    printf("    /use ?[\"team_uuid\"] ?[\"channel_uuid\"] ?[\"thread_uuid\"] ");
    printf(": use specify a context team/channel/thread\n");
    printf("    /create : based on what is being used create the sub ");
    printf("resource (see below)\n");
    printf("    /list : based on what is being used list all the sub ");
    printf("resources (see below)\n");
    printf("    /info : based on what is being used list the ");
    printf("current (see below)\n");
}

int c_help(char *buff, client_t *client)
{
    if (buff[0] != '\n')
        return (CMD_ERROR);
    printf("Commands alvailable :\n");
    printf("    /help : List all the commands alvailable\n");
    printf("    /login [\"Username\"] : set the Username used by client\n");
    printf("    /logout : disconnect the client from the server\n");
    printf("    /users : get the list of all users that exist on the domain\n");
    printf("    /user [\"user_uuid\"] : get information about a user\n");
    printf("    /send [\"user_uuid”\"] [\"message_body\"] : send a message");
    printf(" to a user\n");
    printf("    /messages [\"user_uuid\"] : list all messages exchange");
    printf(" with an user\n");
    printf("    /subscribe [\"team_uuid\"] : subscribe to the event of a team");
    printf(" and its sub directories (enable reception of all events ");
    printf(" from a team)\n");
    printf("    /subscribed ?[\"team_uuid\"] : list all subscribed teams or ");
    printf(" list all users subscribed to a team\n");
    provide_help();
    UNUSED(client);
    return (HELP);
}