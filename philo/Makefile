# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cahn <cahn@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/16 21:03:19 by cahn              #+#    #+#              #
#    Updated: 2023/09/16 22:24:51 by cahn             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra -fsanitize=thread -g
NAME = philo
SRCS = init.c main.c routine.c utility.c
OBJS = ${SRCS:.c=.o}

all	: $(NAME)
$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
%.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $@
clean :
	rm -f $(OBJS)
fclean : clean
	rm -f philo
re : fclean all
.PHONY : all re clean fclean