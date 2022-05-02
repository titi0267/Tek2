##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Makefile
##

SRC =	src/fork_and_execve.c	\
		src/ftrace_command.c	\
		src/path_to_array.c	\
		src/printer.c	\
		src/path_command.c	\
		src/tools.c		\
		src/parse_proc.c	\

MAIN =	src/main.c

INC_PATH =	include

NAME =	ftrace

OBJ = 	$(SRC:.c=.o)

OBJMAIN = 	$(MAIN:.c=.o)

CFLAGS = -I. -I$(INC_PATH) -Wall -Wextra -g

$(NAME):	$(OBJ)	$(OBJMAIN)
		@gcc -o $(NAME) $(OBJ) $(OBJMAIN) $(CFLAGS)

all:	$(NAME)

clean:
		rm -f $(OBJ) $(OBJMAIN)

fclean:	clean
		rm -fr $(NAME)

re:	fclean all
