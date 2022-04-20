/*
** EPITECH PROJECT, 2022
** ftp
** File description:
** socket_create
*/

#include "../include/ftp.h"

fd_set read_fd_set;

int socket_create(char *av)
{
    int sck;
    struct sockaddr_in my_socket;

    sck = socket(PF_INET, SOCK_STREAM, 0);
    my_socket.sin_family = AF_INET;
    my_socket.sin_port = htons(atoi(av));
    my_socket.sin_addr.s_addr = INADDR_ANY;
    if (bind(sck, (struct sockaddr *)&my_socket, sizeof(my_socket)) == -1) {
        printf("Error: Bind failed\n");
        exit(84);
    }
    listen(sck, 5);
    return (sck);
}

int create_list(node_t *front, int connection)
{
    node_t new_node = malloc(sizeof(*new_node));

    if (new_node == NULL)
        return (0);
    new_node->connection = connection;
    new_node->next = (*front);
    (*front) = new_node;
    return (1);
}

void through_list(node_t *head)
{
    node_t list = (*head);

    for (; list != NULL; list = list->next) {
        if (list->connection >= 0) {
            FD_SET(list->connection, &read_fd_set);
        }
    }
}

int add_connection(node_t *list, int new_client)
{
    node_t client = (*list);

    for (; client != NULL; client = client->next) {
        if (client->connection < 0) {
            client->connection = new_client;
            dprintf(client->connection, "220\r\n");
            break;
        }
    }
    return (0);
}

int parse_recieved(char *buf, node_t client)
{
    //dprintf(client->connection, "%s\n", buf);
    if (strcmp(buf, PASS) == 0) {
        dprintf(client->connection, "230 User logged in, proceed.\r\n");
    } else if (strcmp(buf, USER) == 0) {
        dprintf(client->connection, "331 User name okay, need password.\r\n");
    } else {
       dprintf(client->connection, "xxx Error (RFC compliant)\r\n");
    }
}

int check_client_connection(node_t *list, int socket_fd)
{
    node_t client = (*list);
    int ret_val;
    char *buf = malloc(sizeof(char) * 500);

    //client = client->next;
    for (; client != NULL; client = client->next) {
        if (client->connection > 0 && FD_ISSET(client->connection, &read_fd_set)) {
            ret_val = read(client->connection, buf, 500);
            if (ret_val == 0) {
                close(client->connection);
                client->connection = -1;
            }
            if (ret_val > 0) {
                buf[ret_val] = '\0';
                parse_recieved(buf, client);
            }
            if (ret_val == -1) {
                printf("recv() failed for fd: %d []\n", client->connection);
                break;
            }
            ret_val--;
            if (!ret_val)
                continue;
        }
    }
}

int socket_run(char *av)
{
    struct sockaddr_in new_adrr;
    int socket = socket_create(av);
    //fd_set read_fd_set;
    socklen_t adrr_len;
    int new_client;
    node_t client = NULL;
    node_t head = NULL;
    int ret_val;

    for (int i = 0; i < MAX_CLIENT; i++) {
        if (i == MAX_CLIENT - 1)
            create_list(&client, socket);
        else
            create_list(&client, -1);
    }
    head = client;
    while (1) {
        FD_ZERO(&read_fd_set);
        through_list(&head);
        ret_val = select(FD_SETSIZE, &read_fd_set, NULL, NULL, NULL);
        if (ret_val != 0) {
            if (FD_ISSET(socket, &read_fd_set)) {
                printf("Returned fd is %d (server's fd)\n", socket);
                adrr_len = sizeof(struct sockaddr_in);
                new_client = accept(socket, (struct sockaddr*)&new_adrr, &adrr_len);
                if (new_client >= 0) {
                    printf("Accepted a new connection with fd: %d\n", new_client);
                    add_connection(&client, new_client);
                } else {
                    fprintf(stderr, "accept failed []\n");
                }
                ret_val--;
                if (!ret_val)
                    continue;
            }
            check_client_connection(&client, socket);
        }
    }
}