##
## EPITECH PROJECT, 2022
## rush2 [WSL: Ubuntu]
## File description:
## Makefile
##

SRC            =    new.c	\
					point.c	\
					array.c \
					list.c \
					char.c \
					vertex.c \
					string.c \
					int.c \
					player.c \
					float.c \

TESTS_SRC    =    tests/tests_new.c

OBJ            =    $(SRC:%.c=%.o)

INC_DIR        =    ./

CFLAGS        +=    -std=gnu17 -Wall -Wextra

TESTS_NAME    =    string_tests

all: $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(TESTS_NAME)
	rm -f $(wildcard *.gcno)
	rm -f $(wildcard *.gcda)
	rm -f $(wildcard **/.gcno)
	rm -f $(wildcard */.gcda)

tests_run: CFLAGS += --coverage
tests_run: re
	gcc $(OBJ) $(TESTS_SRC) -o $(TESTS_NAME) -lcriterion --coverage
	./$(TESTS_NAME)

re: fclean all