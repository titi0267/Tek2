##
## EPITECH PROJECT, 2022
## B-CCP-400-STG-4-1-panoramix-timothe.coniel
## File description:
## Makefile
##

SRC =	src/main.c			\
		src/parse_args.c	\
		src/threads.c		\

OBJ	=	$(SRC:.c=.o)

NAME	=	panoramix

CFLAGS += -g

all:  $(NAME)

$(NAME):	$(OBJ)
	gcc $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all