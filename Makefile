##
## EPITECH PROJECT, 2020
## B-MUL-100-STG-1-1-myrunner-timothe.coniel
## File description:
## Makefile
##

SRC=	string_handling.c	\

OBJ		=	$(SRC:.c=.o)

NAME	=	libstring.a

all:	$(OBJ)
		ar	rc	$(NAME)		$(OBJ)

clean:
		rm	-f	$(OBJ)

fclean:	clean
		rm	$(NAME)

re:		fclean	all

.PHONY:	all	clean	fclean	re