##
## EPITECH PROJECT, 2022
## Pool
## File description:
## Makefile
##

CC    =    ghc

SRC    =    pushswap_checker.hs

EXEC    =   pushswap_checker 

all:    $(EXEC)

$(EXEC):    $(OBJ)
	$(CC)	-o	$(EXEC)	$(SRC)

clean:
	rm	-rf	*.hi	*.o

fclean:	clean
	rm	-rf	$(EXEC)

re:    fclean all

.PHONY:    clean fclean re all