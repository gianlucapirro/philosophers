# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gianlucapirro <gianlucapirro@student.42    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/25 00:22:23 by gianlucapir       #+#    #+#              #
#    Updated: 2022/10/05 22:43:30 by gianlucapir      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= main.c setup.c util.c philo.c
OBJS	= ${SRCS:.c=.o}
NAME	= philo

.c.o:
	gcc -Wall -Wextra -Werror -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	gcc -o ${NAME} ${OBJS} -lpthread

all: ${NAME}

clean:
	rm -f ${OBJS}

fclean:
	rm -f ${OBJS}
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re .c.o clone