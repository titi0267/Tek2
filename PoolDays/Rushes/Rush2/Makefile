##
## EPITECH PROJECT, 2022
## rush2 [WSL: Ubuntu]
## File description:
## Makefile
##

MAIN_SRC		=	list_main.c
SRC				=	new.c	\
					point.c	\
					array.c \
					list.c \
					char.c \
					vertex.c \
					string.c \
					int.c \
					player.c \
					float.c \

TESTS_SRC    	=    tests/tests_new.c

MAIN_OBJ		=	$(MAIN_SRC:%.c=%.o)
OBJ				=	$(SRC:%.c=%.o)
TESTS_OBJ		=	$(TESTS_SRC:%.c=%.o)

INC_DIR			=	./tests

CFLAGS			+=	-std=gnu17 -Wall -Wextra -I$(INC_DIR)

NAME			=	list_example
TESTS_NAME		=	unit_tests

all: $(NAME)

$(NAME): $(OBJ) $(MAIN_OBJ)
	gcc $(CFLAGS) -o $(NAME) $(OBJ) $(MAIN_OBJ)

clean:
	rm -f $(MAIN_OBJ)
	rm -f $(OBJ)
	rm -f $(TESTS_OBJ)
	rm -f $(wildcard *.gcno)
	rm -f $(wildcard *.gcda)
	rm -f $(wildcard **/.gcno)
	rm -f $(wildcard */.gcda)

fclean: clean
	rm -f $(NAME)
	rm -f $(TESTS_NAME)

tests_run: CFLAGS += --coverage
tests_run: re $(TESTS_OBJ)
	gcc $(OBJ) $(TESTS_OBJ) -o $(TESTS_NAME) -lcriterion --coverage
	./$(TESTS_NAME)

re: fclean all