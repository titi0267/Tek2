##
## EPITECH PROJECT, 2022
## ftp
## File description:
## Makefile
##

SRC =	src/main.c			\
		src/parse_args.c	\
		src/server.c		\
		src/server_loop.c	\
		src/client_list.c	\
		src/client_part.c	\
		src/commands/user.c	\
		src/commands/pass.c	\
		src/commands/noop.c	\
		src/commands/quit.c	\
		src/commands/help.c	\
		src/commands/path.c	\
		src/commands/cdup.c	\
		src/commands/cwd.c	\

OBJ	=	$(SRC:.c=.o)

NAME	=	myftp

CFLAGS += -g

all:  $(NAME)

$(NAME):	$(OBJ)
	gcc $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all