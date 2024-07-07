# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zaldhahe <zaldhahe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/07 20:59:41 by zaldhahe          #+#    #+#              #
#    Updated: 2024/07/07 21:46:45 by zaldhahe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = philo.c checker.c utils1.c\

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Werror -Wextra

COMPILE = $(CC) $(CFLAGS)

all : $(NAME)

$(NAME) : $(OBJ)
	$(COMPILE) $(OBJ) -o $(NAME)

$(NAME) : $(OBJ)
	$(COMPILE) $(OBJ) -o $(NAME)

clean : 
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re