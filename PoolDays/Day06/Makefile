##
## EPITECH PROJECT, 2022
## Pool
## File description:
## Makefile
##

CC    =    g++

SRC    =    ex00/cat.cpp			\

EXEC    =   my_cat

all:    $(EXEC)

$(EXEC):    $(OBJ)
	$(CC)	-o	$(EXEC)	$(SRC)	-g

clean:
	rm	-rf	*.o

fclean:	clean
	rm	-rf	$(EXEC)

re:    fclean all

.PHONY:    clean fclean re all