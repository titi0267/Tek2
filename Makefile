##
## EPITECH PROJECT, 2020
## makefile
## File description:
## make
##

MAIN_SRC            =    Src/main.cpp

SRC =	Src/Encapsulations/Mutex/CMutex.cpp		\
		Src/Encapsulations/Fork/CFork.cpp		\
		Src/Encapsulations/Wait/Wait.cpp		\
		Src/Encapsulations/Threads/CThreads.cpp		\
		Src/Encapsulations/FIFO/CFifo.cpp		\
		Src/Encapsulations/ConditionnalVar/ConditionnalVar.cpp		\
		Src/Reception/Reception.cpp		\
		Src/Reception/Order.cpp		\
		Src/Pizza/Margarita.cpp		\
		Src/Pizza/Fantasia.cpp		\
		Src/Pizza/Americana.cpp		\
		Src/Pizza/Regina.cpp		\
		Src/Kitchen/ThreadPull.cpp		\
		Src/Kitchen/ThreadPayload.cpp		\
		Src/Error/Error.cpp		\
		Src/Utils/Utils.cpp		\
		Src/Kitchen/Stock.cpp		\
		Src/Kitchen/Kitchen.cpp

MAIN_OBJ            =    $(MAIN_SRC:.cpp=.o)
OBJ                    =    $(SRC:.cpp=.o)

NAME                =    plazza

CXXFLAGS += 	-lpthread

all: $(NAME)

$(NAME): $(MAIN_OBJ) $(OBJ)
	g++ -o $(NAME) $(MAIN_OBJ) $(OBJ) $(CXXFLAGS)

debug: CXXFLAGS += -g
debug: re

clean:
	rm -f $(MAIN_OBJ)
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all