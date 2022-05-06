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
				server/src/list/lib.c

SRC_CLIENT	=	client/src/main.c		\
				client/src/setup.c

OBJ_SERVER		=	$(SRC_SERVER:.c=.o)

OBJ_CLIENT = 	$(SRC_CLIENT:.c=.o)

NAME_SERVER		=	myteams_server

NAME_CLIENT	=	myteams_cli

CFLAGS 		+= 		-ldl	-g

all:	$(NAME_SERVER)

$(NAME_SERVER): $(OBJ_SERVER) $(OBJ_CLIENT)
		gcc -o $(NAME_SERVER) $(OBJ_SERVER) $(CFLAGS)
		gcc -o $(NAME_CLIENT) $(OBJ_CLIENT)

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