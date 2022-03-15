##
## EPITECH PROJECT, 2022
## B-MAT-400-STG-4-1-203hotline-timothe.coniel
## File description:
## Makefile
##


CC	=	gcc		-o

SRC	=	main.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Wall	-Wextra	-pedantic	--std=c99	-I./	-g

NAME	=	203hotline

all:	$(OBJ)
	$(CC)	$(NAME)	$(OBJ)	$(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm	-f	$(NAME)

re:	fclean	all

.PHONY:	all	clean	fclean	re