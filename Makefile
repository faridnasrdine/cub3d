SRCS = main.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
	   parsing/parsing.c  parsing/parsing_utils2.c parsing/parsing_utils1.c RayCasting.c

OBJS = ${SRCS:.c=.o}

NAME = cub3d
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
LDFLAGS = -L./minilibx-linux/ -lmlx_Linux -lXext -lX11

LIBFT = libft/libft.a

${NAME}: ${OBJS}
	cd libft && ${MAKE}
	cd minilibx-linux && ${MAKE}
	${CC} ${CFLAGS} ${OBJS} ${LIBFT} ${LDFLAGS} -o ${NAME}

all: ${NAME}

clean:
	cd libft && ${MAKE} clean
	rm -f ${OBJS}

fclean: clean
	cd libft && ${MAKE} fclean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re