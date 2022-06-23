##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## Makefile
##

NAME =    209poll

$(NAME):
		cargo build --release
		cp "./target/release/poll" "./$(NAME)"

all:    $(NAME)

clean:
		cargo clean

fclean:    clean
		rm -fr $(NAME)

re:    fclean all