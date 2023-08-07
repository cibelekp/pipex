# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ckojima- <ckojima-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/06 22:08:20 by ckojima-          #+#    #+#              #
#    Updated: 2023/08/06 22:08:20 by ckojima-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= pipex
SOURCES			= ${NAME}.c utils.c utils2.c
OBJECTS			= ${SOURCES:.c=.o}
CC				= cc\

CFLAGS			= -Wall -Wextra -Werror -g
# CFLAGS		+= -fsanitize=address -fsanitize=undefined
RM				= rm -rf

#Libft
LIBFT = ./libft/libft.a
LIBFT_PATH = ./libft

#Colors
GREEN=\033[0;32m
END=\033[0m

#Silencing makefile
$(VERBOSE).SILENT:

all: ${NAME}

${NAME}: ${OBJECTS}
	make -C $(LIBFT_PATH)
	@echo "$(GREEN)******** libft compiled ********$(END)"
	${CC} ${CFLAGS} ${OBJECTS} $(LIBFT) -o ${NAME}
	@echo "$(GREEN)******** ${NAME} compiled ********$(END)"

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

clean:
	make clean -C $(LIBFT_PATH)
	${RM} ${OBJECTS}
	@echo "$(GREEN)******** everything clean ********$(END)"

fclean: clean
	make fclean -C $(LIBFT_PATH)
	${RM} ${NAME} ${NAME}
	@echo "$(GREEN)******** ${NAME} removed ********$(END)"

re: fclean all

.PHONY: all, clean, fclean, re
