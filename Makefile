##
## EPITECH PROJECT, 2022
## B-PSU-400-STG-4-1-nmobjdump-timothe.coniel
## File description:
## Makefile
##

CC	=	gcc		-o

SRC	=	flag_f.c	\
		main.c

CFLAGS	=	-Wall	-Wextra	-pedantic	--std=c99	-I./	-g

NAME	=	objdump

all:
	$(CC)	$(NAME)	$(SRC)	$(CFLAGS)

clean:

fclean: clean
	rm	-f	$(NAME)

re:	fclean	all

.PHONY:	all	clean	fclean	re