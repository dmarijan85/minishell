# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmarijan <dmarijan@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/03 11:33:35 by dmarijan          #+#    #+#              #
#    Updated: 2024/10/09 14:13:19 by dmarijan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =	lexer.c			\
		main.c			\
		#parser.c		\
		#bomboclaat.c	\
		#main_bonus.c	\
		#utils_bonus.c	\

OBJ = $(SRC:.c=.o)

COMPILE = gcc -Wall -Werror -Wextra -g

REMOVE = rm -f

READLINE_LIB = -lreadline -L /Users/$(USER)/.brew/opt/readline/lib \
-I /Users/$(USER)/.brew/opt/readline/include

all: $(NAME) $(BONUS)

$(NAME): Makefile minishell.h $(OBJ)
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
