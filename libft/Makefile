# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmarijan <dmarijan@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/09 12:42:37 by dmarijan          #+#    #+#              #
#    Updated: 2024/04/11 13:28:34 by dmarijan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC = ft_printetc.c ft_printf.c ft_putnbr_fd.c \
	  ft_putunsigned.c ft_printhex.c ft_printptr.c \

OBJ = ${SRC:.c=.o}

COMPILE = gcc -Wall -Werror -Wextra -c

LIB = ar rc $(NAME)

REMOVE = rm -f

LIBFT = libft

all: $(NAME)

$(NAME): Makefile ft_printf.h $(OBJ)
	make all bonus -C $(LIBFT)
	cp libft/libft.a .
	mv libft.a $(NAME)
	@$(COMPILE) $(SRC)
	$(LIB) $(OBJ)

clean:
	make clean -C libft
	$(REMOVE) $(OBJ)
	$(REMOVE) $(OBJ_BONUS)

fclean: clean
	make fclean -C libft
	$(REMOVE) $(NAME)

re: fclean all

.PHONY = all clean fclean re
