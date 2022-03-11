##
## EPITECH PROJECT, 2022
## B-PSU-400-STG-4-1-nmobjdump-timothe.coniel
## File description:
## Makefile
##

CC	=	gcc		-o

SRC_OBJ	=	src_objdump/elf64.c			\
		src_objdump/elf64_bis.c		\
		src_objdump/parsing.c		\
		src_objdump/elf32.c			\
		src_objdump/main.c

SRC_NM =	src_nm/main.c		\

CFLAGS	=	-Wall	-Wextra	-pedantic	--std=c99	-I./

NAME_OBJ	=	my_objdump

NAME_NM		=	my_nm

nm:
	$(CC)	$(NAME_NM)	$(SRC_NM)	$(CFLAGS)

objdump:
	$(CC)	$(NAME_OBJ)	$(SRC_OBJ)	$(CFLAGS)

all:	nm	objdump

clean:

fclean: clean
	rm	-f	$(NAME_OBJ)
	rm	-f	$(NAME_NM)

re:	fclean	all

.PHONY:	nm	objdump	all	clean	fclean	re