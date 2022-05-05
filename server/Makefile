##
## EPITECH PROJECT, 2020
## bootstrap
## File description:
## Makefile
##

SRC		=	src/main.c		\
			src/setup.c		\
			src/loop.c		\
			src/free.c		\
			src/list/lib.c

OBJ		=	$(SRC:.c=.o)

NAME	=	myteams

CFLAGS += -Wall -Wextra -g

all: $(NAME)
	make clean

$(NAME): $(OBJ)
		gcc -o $(NAME) $(OBJ) $(CFLAGS)

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re