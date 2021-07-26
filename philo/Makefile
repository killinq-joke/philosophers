# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/19 17:26:03 by ztouzri           #+#    #+#              #
#    Updated: 2021/07/26 12:08:52 by ztouzri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INCLUDES= philo.h
SRCS	= main.c utils.c inits.c parsing.c time.c routines.c
OBJS	= $(SRCS:c=o)
NAME	= philo
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g -fsanitize=address

all:	$(NAME) $(INCLUDES)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lpthread

%o:		%c
	$(CC) $(CFLAGS) $< -c

clean:
	$(RM) $(OBJS)

fclean:		clean
	$(RM) $(NAME)

re:			fclean all
