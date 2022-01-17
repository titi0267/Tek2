##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## Makefile
##

CC		=	gcc	-o

SRC=		z.c		\

CFLAGS	=	-std=gnu17 -Wall -Wextra

NAME	=	z

all:
	$(CC)	$(NAME)	$(SRC)	$(CFLAGS)

clean:
	rm	-f	$(OBJ)

fclean: clean
	rm	-f	$(NAME)

re:	fclean	all

.PHONY:	all	clean	fclean	re