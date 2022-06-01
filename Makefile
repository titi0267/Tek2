##
## EPITECH PROJECT, 2020
## bootstrap
## File description:
## Makefile
##

SRC_SERVER		=	server/src/main.c		\
				server/src/setup.c		\
				server/src/loop.c		\
				server/src/free.c		\
				server/src/list/lib.c		\
				server/src/command/command_main.c		\
				server/src/command/login.c		\
				server/src/utils/convertion.c		\
				server/src/command/user.c		\
				server/src/command/users.c		\
				server/src/utils/connected.c		\
				server/src/command/send.c		\
				server/src/utils/exist.c		\
				server/src/command/messages.c		\
				server/src/command/subscribe.c		\
				server/src/command/unsubscribe.c		\
				server/src/command/logout.c		\
				server/src/utils/print_allusers.c	\
				server/src/utils/save_architecture.c

SRC_CLIENT	=	client/src/main.c		\
				client/src/setup.c		\
				client/src/loop.c		\
				client/src/free.c		\
				client/src/parse_cmd.c	\
				client/src/commands/all_users.c \
				client/src/commands/create.c \
				client/src/commands/logout.c \
				client/src/commands/help.c \
				client/src/commands/info.c \
				client/src/commands/list.c \
				client/src/commands/login.c \
				client/src/commands/messages.c \
				client/src/commands/send.c \
				client/src/commands/subscribe.c \
				client/src/commands/subscribed.c \
				client/src/commands/unsubscribed.c \
				client/src/commands/use.c \
				client/src/commands/user.c \
				client/src/check_valid_args.c \
				client/src/get_server_reply.c	\
				client/src/server_reply/create.c	\
				client/src/server_reply/info.c		\
				client/src/server_reply/list.c	\
				client/src/server_reply/login.c		\
				client/src/server_reply/logout.c	\
				client/src/server_reply/messages.c	\
				client/src/server_reply/send.c		\
				client/src/server_reply/subscribe.c	\
				client/src/server_reply/subscribed.c	\
				client/src/server_reply/unsubscribe.c	\
				client/src/server_reply/user.c		\
				client/src/server_reply/users.c		\

OBJ_SERVER		=	$(SRC_SERVER:.c=.o)

OBJ_CLIENT = 	$(SRC_CLIENT:.c=.o)

NAME_SERVER		=	myteams_server

NAME_CLIENT	=	myteams_cli

CFLAGS 		+= 		-g

all:	$(NAME_SERVER)

$(NAME_SERVER): $(OBJ_SERVER) $(OBJ_CLIENT)
		gcc -o $(NAME_SERVER) $(OBJ_SERVER) $(CFLAGS) -Llibs/myteams -lmyteams
		gcc -o $(NAME_CLIENT) $(OBJ_CLIENT) $(CFLAGS) -Llibs/myteams -lmyteams

server: $(OBJ_SERVER)
		gcc -o $(NAME_SERVER) $(OBJ_SERVER) $(CFLAGS)

client: $(OBJ_CLIENT)
		gcc -o $(NAME_CLIENT) $(OBJ_CLIENT)

clean:
		rm -f $(OBJ_SERVER)
		rm -f $(OBJ_CLIENT)

fclean: clean
		rm -f $(NAME_SERVER)
		rm -f $(NAME_CLIENT)

re: fclean all

.PHONY: all comp clean fclean re