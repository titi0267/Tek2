##
## EPITECH PROJECT, 2020
## makefile
## File description:
## make
##

MAIN_SRC            =    Src/plazza.cpp

SRC = 		Src/Mutex/CMutex.cpp

MAIN_OBJ            =    $(MAIN_SRC:.cpp=.o)
OBJ                    =    $(SRC:.cpp=.o)

NAME                =    plazza

CFLAGS += -lpthread

all: $(NAME)

$(NAME): $(MAIN_OBJ) $(OBJ)
	g++ -o $(NAME) $(MAIN_OBJ) $(OBJ) $(CFLAGS)

clean:
	rm -f $(MAIN_OBJ)
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)