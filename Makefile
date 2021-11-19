# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgangaro <cgangaro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/08 15:43:11 by cgangaro          #+#    #+#              #
#    Updated: 2021/11/09 15:03:29 by cgangaro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo
PATH		= 	srcs
SRCS_NAME	=	main.c \
				utils.c \
				ft_atoi.c \
				philo.c \
				parsing.c \
				time.c
OBJS		= ${SRCS:.c=.o}
FLAGS		= -Wall -Werror -Wextra
SRCS		= $(addprefix ${PATH}/,${SRCS_NAME})
%.o: %.c ./inc/philosopher.h
		gcc $(FLAGS) -c $< -o $@
all:	$(NAME)
$(NAME) : $(OBJS)
			gcc $(FLAGS) $(OBJS)  -o $(NAME)
clean:
	rm -f $(OBJS)
fclean:
	rm -f $(OBJS) $(NAME)
re: fclean all
norme:
	@norminette $(SRCS) inc/philosopher.h