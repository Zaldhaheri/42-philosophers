# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zaldhahe <zaldhahe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/08 17:20:41 by zaldhahe          #+#    #+#              #
#    Updated: 2024/09/08 17:20:41 by zaldhahe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = philo.c philo_init.c philo_utils1.c parsing.c free.c \
		utils1.c utils2.c utils3.c 

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Werror -Wextra -pthread -g3

COMPILE = $(CC) $(CFLAGS)

all : $(NAME)

$(NAME) : $(OBJ) 
	$(COMPILE) $(OBJ) -o $(NAME)

clean : 
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re