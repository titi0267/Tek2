##
## EPITECH PROJECT, 2022
## B-ASM-400-STG-4-1-asmminilibc-timothe.coniel
## File description:
## Makefile
##

SRC    =    lib/strlen.asm      \
			lib/strchr.asm		\
			lib/strrchr.asm		\
			lib/memset.asm		\
			lib/memcpy.asm		\
			lib/strcmp.asm		\
			lib/memmove.asm		\
			lib/strncmp.asm

OBJ=    $(SRC:.asm=.o)

NAME=    libasm.so

CFLASG    =    -shared -fPIC

all:    $(NAME)

%.o	:	%.asm
	nasm	-o	$@	$<	-f	elf64

$(NAME):    $(OBJ)
	ld	$(CFLASG)	-o	$(NAME)	$(OBJ)

clean:
	rm	-f	$(OBJ)

fclean:	clean
	rm	-f	$(NAME)

re:	fclean	all

.PHONY:    all    clean    fclean    re