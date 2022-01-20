##
## EPITECH PROJECT, 2020
## B-MUL-100-STG-1-1-myrunner-timothe.coniel
## File description:
## Makefile
##

SRC=	assign.c			\
		append.c			\
		c_d_tor.c			\
		at.c				\
		clear.c				\
		length.c			\
		compare.c			\
		copy.c				\
		c_str.c				\
		empty.c				\

OBJ		=	$(SRC:.c=.o)

NAME	=	libstring.a

all:	$(OBJ)
		ar	rc	$(NAME)		$(OBJ)

clean:
		rm	-f	$(OBJ)

fclean:	clean
		rm	-f	$(NAME)

re:		fclean	all

.PHONY:	all	clean	fclean	re