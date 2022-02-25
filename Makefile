##
## EPITECH PROJECT, 2020
## makefile
## File description:
## make
##

SRC =	src/main.cpp	\
		src/utils.cpp	\
		src/Chipsets.cpp	\

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