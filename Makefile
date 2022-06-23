##
## EPITECH PROJECT, 2022
## B-PDG-300-STG-3-1-PDGD09-ludovic.sutter
## File description:
## Makefile
##

SRC        =    Peasant.cpp    \
        Knight.cpp    \
        Enchanter.cpp \
        Paladin.cpp \
        Priest.cpp

TESTS_SRC        =    tests/tests_new.cpp

TESTS_OBJ        =    $(TESTS_SRC:%.cpp=%.o)

NAME        =    unit_tests

OBJ                =    $(SRC:%.cpp=%.o)

CPPFLAGS += --std=c++17 --coverage

all: $(NAME)

$(NAME): $(OBJ) $(TESTS_OBJ)
	g++ $(OBJ) $(TESTS_OBJ) -o $(NAME) -lcriterion --coverage

clean:
	rm -f $(OBJ) $(TESTS_OBJ)
	rm -f $(wildcard *.gcno)
	rm -f $(wildcard *.gcda)
	rm -f $(wildcard **/.gcno)
	rm -f $(wildcard */.gcda)

fclean: clean
	rm -f $(NAME)

tests_run: re
	./$(NAME)

re: fclean $(NAME)