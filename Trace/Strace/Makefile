##
## EPITECH PROJECT, 2022
## B-PSU-402-STG-4-1-strace-timothe.coniel
## File description:
## Makefile
##

SRC =	src/main.c			\
		src/no_options.c	\
		src/p_flag.c		\
		src/s_flag.c		\

OBJ	=	$(SRC:.c=.o)

NAME	=	strace

CFLAGS += -g

all:  $(NAME)

$(NAME):	$(OBJ)
	gcc $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all