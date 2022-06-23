##
## EPITECH PROJECT, 2020
## makefile
## File description:
## make
##

SRC =	core.cpp	\
		utils/get_file.cpp	\
		ncurses/ncurses.cpp	\
		sfml/create_modules.cpp	\
		sfml/printInfo.cpp

OBJ	=	$(SRC:.cpp=.o)

NAME	=	MyGKrellm

CFLAGS += -g -lsfml-graphics -lsfml-window -lsfml-system

all:  $(NAME)

$(NAME):	$(OBJ)
	g++ $(OBJ) -o $(NAME)	$(CFLAGS) -lncurses

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all