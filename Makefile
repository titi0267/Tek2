##
## EPITECH PROJECT, 2020
## makefile
## File description:
## make
##

MAIN_SRC            =    src/main.cpp

SRC =	src/Utils/Utils.cpp	\
		src/Chipsets.cpp	\
		src/Error/Error.cpp		\
		src/createComponent/Components.cpp \
		src/createComponent/Factory.cpp		\
		src/specialComponent/source/Input.cpp	\
		src/specialComponent/source/Output.cpp	\
		src/specialComponent/source/False.cpp	\
		src/specialComponent/source/True.cpp	\
		src/specialComponent/source/Clock.cpp	\
		src/Simulate/Simulate.cpp	\
		src/gates/Gates.cpp		\
		src/createComponent/Link.cpp	\
		src/createComponent/source/Comp4069.cpp		\
		src/createComponent/source/Comp4081.cpp		\
		src/createComponent/source/Comp4071.cpp		\
		src/createComponent/source/Comp4001.cpp		\
		src/createComponent/source/Comp4011.cpp		\
		src/createComponent/source/Comp4030.cpp		\

TESTS_SRC		= 		tests/test_main.cpp

GCNO_FILES            =    $(SRC:.cpp=.gcno) $(TESTS_SRC:.cpp=.gcno)
GCDA_FILES            =    $(SRC:.cpp=.gcda) $(TESTS_SRC:.cpp=.gcda)

MAIN_OBJ            =    $(MAIN_SRC:.cpp=.o)
OBJ                    =    $(SRC:.cpp=.o)
TESTS_OBJ            =    $(TESTS_SRC:.cpp=.o)

NAME                =    nanotekspice
NAME_TESTS            =    unit_tests

all: $(NAME)

$(NAME): $(MAIN_OBJ) $(OBJ)
	g++ -o $(NAME) $(MAIN_OBJ) $(OBJ)

tests_run: CXXFLAGS += --coverage
tests_run: fclean $(OBJ) $(TESTS_OBJ)
	g++ $(CXXFLAGS) -o $(NAME_TESTS) $(OBJ) $(TESTS_OBJ) -lcriterion
	./$(NAME_TESTS)

debug: CXXFLAGS += -g
debug: re

clean:
	rm -f $(MAIN_OBJ)
	rm -f $(OBJ)
	rm -f $(TESTS_OBJ)
	rm -f $(GCNO_FILES)
	rm -f $(GCDA_FILES)

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_TESTS)

re: fclean all