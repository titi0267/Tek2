##
## EPITECH PROJECT, 2022
## Pool
## File description:
## Makefile
##

CC    =    g++

CFLAGS	=	-std=c++20 -Wall -Wextra -Werror

SRC    =    convert_temp.cpp			\

EXEC    =   my_convert_temp

all:    $(EXEC)

$(EXEC):    $(OBJ)
	$(CC)	-o	$(EXEC)	$(SRC)	$(CFLAGS)

clean:
	rm	-rf	*.o

fclean:	clean
	rm	-rf	$(EXEC)

re:    fclean all

.PHONY:    clean fclean re all