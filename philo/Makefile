NAME		= philo
CC		= cc
CFLAGS		= -Wall -Wextra -Werror -pthread
RM		= rm -rf

SRC_DIR		= ./
OBJ_DIR		= obj/
INCLUDE		= -I .

SRCS		= ${SRC_DIR}main.c \
		  ${SRC_DIR}input_check.c \
		  ${SRC_DIR}utils.c \
		  ${SRC_DIR}init.c \
		  ${SRC_DIR}safe_functions.c \
		  ${SRC_DIR}threads.c \
		  ${SRC_DIR}routine.c \
		  ${SRC_DIR}monitor.c \

OBJS		= ${SRCS:${SRC_DIR}%.c=${OBJ_DIR}%.o}

all:		${OBJ_DIR} ${NAME}

${NAME}:	${OBJS}
			${CC} ${CFLAGS} ${OBJS} ${INCLUDE} -o ${NAME}

${OBJ_DIR}:
			@mkdir -p ${OBJ_DIR}

${OBJ_DIR}%.o:	${SRC_DIR}%.c
			@mkdir -p ${@D}
			${CC} ${CFLAGS} ${INCLUDE} -c $< -o $@

clean:		
			${RM} ${OBJ_DIR}

fclean:		clean
			${RM} ${NAME} ${NAME_BONUS}

re:		fclean all

.PHONY:		all bonus clean fclean re
