NAME	=	philosophers
VPATH	=	./includes/ ./utils/
SRCS	=	main.c\
			init.c\
			error.c\
			time.c\
			action.c\
			mutex.c
OBJS	= 	${SRCS:.c=.o}
CC		= 	gcc
CFLAGS	= 	-g -pthread -Werror -Wextra -Wall
OBJ_DIR	=	./objs/
INC_DIR	=	./includes/
UTILS	=	utils/utils.a

all: ${NAME}

$(NAME): $(UTILS) $(OBJS)
	$(CC) ${CFLAGS} -o $(NAME) $(OBJS) $(UTILS)

%.o: %.c
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(UTILS):
	make -C utils

clean:
	make clean -C utils
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME} $(UTILS)

re: fclean all

.PHONY: all clean fclean re .c.o