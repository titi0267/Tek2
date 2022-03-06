##
## EPITECH PROJECT, 2020
## makefile
## File description:
## make
##

SRC =	src/main.cpp	\
		src/Utils/Utils.cpp	\
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

OBJ	=	$(SRC:.cpp=.o)

NAME	=	nanotekspice

CFLAGS += -g

all:  $(NAME)

$(NAME):	$(OBJ)
	g++ $(OBJ) -o $(NAME)	$(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:	all re clean fclean