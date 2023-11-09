# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdias-ba <rdias-ba@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/21 00:14:33 by rdias-ba          #+#    #+#              #
#    Updated: 2023/11/09 16:45:53 by rdias-ba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				= philo
CC					= cc
CFLAGS				= -Wextra -Werror -Wall -lpthread #-g -fsanitize=thread

SRCS		= srcs/init.c srcs/error.c srcs/main.c srcs/utils.c srcs/philo.c

all: $(NAME)

$(NAME):	$(SRCS_DIR)
			$(CC) $(CFLAGS) $(SRCS) -o $@

clean: 
			rm -rf $(NAME)

fclean: clean
			rm -rf $(NAME)

re:	fclean all

.PHONY: all clean fclean re
