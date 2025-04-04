NAME		= philo_bonus
CC		= cc
CFLAGS		= -Wall -Wextra -Werror
RM		= rm -rf

SRC_DIR		= ./
OBJ_DIR		= obj/
INCLUDE		= -I .

SRCS		= ${SRC_DIR}main_bonus.c \
		  ${SRC_DIR}input_check_bonus.c \
		  ${SRC_DIR}utils_bonus.c \
		  ${SRC_DIR}init_bonus.c \
		  ${SRC_DIR}processes_bonus.c \
		  ${SRC_DIR}routine_bonus.c \

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
