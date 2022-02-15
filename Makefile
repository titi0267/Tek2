##
## EPITECH PROJECT, 2022
## B-PSU-400-STG-4-1-malloc-timothe.coniel
## File description:
## Makefile
##

CC = gcc

SRC	=	malloc.c

OBJ = $(SRC:.c=.o)

CFLAGS += -fPIC

NAME	=	libmy.so

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC)	-shared	-o	$(NAME)	$(OBJ)

clean:
	rm -f $(OBJ)

fclean:
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re