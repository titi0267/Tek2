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
		src_objdump/parsing_bis.c	\
		src_objdump/main.c

SRC_NM =	src_nm/main.c	\
			src_nm/elf32.c	\
			src_nm/elf64.c	\
			src_nm/parsing.c	\
			src_nm/elf64_bis.c	\
			src_nm/linked_list.c	\
			src_nm/linked_list_bis.c	\
			src_nm/format_string.c	\
			src_nm/parsing_bis.c	\
			src_nm/sort_list.c

OBJS_OBJ	=	$(SRC_OBJ:.c=.o)

OBJS_NM	=	$(SRC_NM:.c=.o)

CFLAGS	=	-Wall	-Wextra	-pedantic	--std=c99	-I./	-g

NAME_OBJ	=	my_objdump

NAME_NM		=	my_nm

all:	nm	objdump

nm:		$(OBJS_NM)
	$(CC)	$(NAME_NM)	$(OBJS_NM)	$(CFLAGS)

objdump:	$(OBJS_OBJ)
	$(CC)	$(NAME_OBJ)	$(OBJS_OBJ)	$(CFLAGS)

clean:
	rm -f $(OBJS_NM)
	rm -f $(OBJS_OBJ)

fclean: clean
	rm	-f	$(NAME_OBJ)
	rm	-f	$(NAME_NM)

re:	fclean	all

.PHONY:	nm	objdump	all	clean	fclean	re