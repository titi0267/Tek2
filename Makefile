##
## EPITECH PROJECT, 2022
## Pool
## File description:
## Makefile
##

CC    =    ghc

SRC    =    DoOp.hs

EXEC    =    doop

all:    $(EXEC)

$(EXEC):    $(OBJ)
    $(CC) -o $(EXEC) $(SRC)

clean:
    rm -rf *.hi *.o
    rm -f DoOp.hi
    rm -f DoOp.o

fclean: clean
    rm -rf $(EXEC)

re:    fclean all

.PHONY: clean fclean re all