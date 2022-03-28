##
## EPITECH PROJECT, 2021
## B-CPE-200-STG-2-1-dante-maxime.hoffbeck
## File description:
## Makefile
##

SRC =	main.c			\

OBJ	=	$(SRC:.c=.o)

NAME	=	204ducks

CFLAGS += -g

all:  $(NAME)

$(NAME):	$(OBJ)
	gcc $(OBJ) -o $(NAME) -lm

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all