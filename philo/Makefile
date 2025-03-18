NAME		= philo
NAME_BONUS	= philo_bonus
CC		= cc
CFLAGS		= -Wall -Wextra -Werror
RM		= rm -rf

SRC_DIR		= ./
OBJ_DIR		= obj/
INCLUDE		= -I .

SRCS		= ${SRC_DIR}main.c \
		  ${SRC_DIR}input_check.c \
		  ${SRC_DIR}utils.c \
		  ${SRC_DIR}init.c \
#SRCS_BONUS	= ${SRC_DIR}main_bonus.c

OBJS		= ${SRCS:${SRC_DIR}%.c=${OBJ_DIR}%.o}
#OBJS_BONUS	= ${SRCS_BONUS:${SRC_DIR}%.c=${OBJ_DIR}%.o}

all:		${OBJ_DIR} ${NAME}

${NAME}:	${OBJS}
			${CC} ${CFLAGS} ${OBJS} ${INCLUDE} -o ${NAME}

${OBJ_DIR}:
			@mkdir -p ${OBJ_DIR}

${OBJ_DIR}%.o:	${SRC_DIR}%.c
			@mkdir -p ${@D}
			${CC} ${CFLAGS} ${INCLUDE} -c $< -o $@

#bonus:		${OBJ_DIR} ${NAME_BONUS}

#${NAME_BONUS}:	${OBJS_BONUS}
#			${CC} ${CFLAGS} ${OBJS_BONUS} ${INCLUDE} -o ${NAME_BONUS}

clean:		
			${RM} ${OBJ_DIR}

fclean:		clean
			${RM} ${NAME} ${NAME_BONUS}

re:		fclean all

.PHONY:		all bonus clean fclean re
