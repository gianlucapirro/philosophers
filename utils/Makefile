# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: gpirro <gpirro@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2021/10/15 17:47:15 by gpirro        #+#    #+#                  #
#    Updated: 2022/04/07 12:32:13 by gpirro        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

SRCS	=	ft_atoi.c\
			ft_bzero.c\
			ft_calloc.c\
			ft_isalnum.c\
			ft_isalpha.c\
			ft_isascii.c\
			ft_isdigit.c\
			ft_isprint.c\
			ft_itoa.c\
			ft_memchr.c\
			ft_memcmp.c\
			ft_memcpy.c\
			ft_memmove.c\
			ft_memset.c\
			ft_putchar_fd.c\
			ft_putendl_fd.c\
			ft_putnbr_fd.c\
			ft_putstr_fd.c\
			ft_split.c\
			ft_strchr.c\
			ft_strdup.c\
			ft_striteri.c\
			ft_strjoin.c\
			ft_strlcat.c\
			ft_strlcpy.c\
			ft_strlen.c\
			ft_strmapi.c\
			ft_strncmp.c\
			ft_strnstr.c\
			ft_strrchr.c\
			ft_strtrim.c\
			ft_substr.c\
			ft_tolower.c\
			ft_toupper.c\
			ft_strtol.c\
			input.c
VPATH	=	../includes/	
INC_DIR	=	../includes/	
OBJS	=	${SRCS:.c=.o}
NAME	=	utils.a

${NAME}: ${OBJS}
	ar rc ${NAME} ${OBJS}

.c.o:
	gcc -Wall -Wextra -Werror -I $(INC_DIR) -c $< -o ${<:.c=.o}


all: ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re .c.o norm