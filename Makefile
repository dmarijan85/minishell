# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmarijan <dmarijan@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/03 11:33:35 by dmarijan          #+#    #+#              #
#    Updated: 2024/11/21 15:32:18 by dmarijan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =	lexer.c			\
		main.c			\
		utils.c			\
		wordsplit.c		\
		cleaners.c		\
		utils_two.c		\
		parser.c		\
		bomboclaat.c	\
		donepezilo.c	\
		builtins.c		\
		utils_three.c	\
		wildproject.c	\
		unset.c			\
		init.c			\
		cedepuntoce.c	\
		redflags.c

OBJ = $(SRC:.c=.o)

COMPILE = gcc -Wall -Werror -Wextra -g -fsanitize=address

REMOVE = rm -f

READLINE_LIB = -lreadline -L /Users/$(USER)/.brew/opt/readline/lib \
-I /Users/$(USER)/.brew/opt/readline/include

all: $(NAME) $(BONUS)

$(NAME): Makefile ./inc/minishell.h $(OBJ)
	make all -C libft
	@$(COMPILE) $(SRC) libft/libftprintf.a  $(READLINE_LIB) -o $(NAME)

clean:
	make clean -C libft
	$(REMOVE) $(OBJ)

fclean: clean
	make fclean -C libft
	$(REMOVE) $(NAME)

re: fclean all

.PHONY = all clean fclean re bonus
