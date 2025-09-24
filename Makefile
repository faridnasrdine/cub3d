SRCS = main.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
	   parsing/parsing.c  parsing/parsing_utils2.c parsing/parsing_utils1.c

OBJS = ${SRCS:.c=.o}

NAME = cub3d
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}

all: ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re