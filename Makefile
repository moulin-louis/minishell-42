# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/13 11:42:25 by bschoeff          #+#    #+#              #
#    Updated: 2022/09/27 12:03:41 by loumouli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ################################## #
#               COMMAND              #
# ################################## #
CC			= cc
MKDIR		= mkdir -p
RM			= rm -rf

# ################################## #
#              EXEC NAME             #
# ################################## #
NAME		= minishell

# ################################## #
#               SOURCES              #
# ################################## #
C_DIR		= src
C_FILES		= main.c		\
			  bi_pwd.c		\


SRCS		= $(patsubst %, $(C_DIR)/%, $(C_FILES))

# ################################## #
#               OBJECTS              #
# ################################## #
O_DIR		= objs
O_FILES		= $(C_FILES:.c=.o)
OBJS		= $(patsubst %, $(O_DIR)/%, $(O_FILES))
DEPS 		= $ $(C_FILES:.c=.d)

# ################################## #
#                FLAGS               #
# ################################## #
CFLAGS		= -Wall -Wextra -Werror -g3 -MMD
CINCLUDES	=	-I ./inc \
				-I ./libft


LIBFT		= ./libft/libft.a

# ################################## #
#                RULES               #
# ################################## #

$(O_DIR)/%.o: $(C_DIR)/%.c
			$(CC) $(CFLAGS) $(CINCLUDES) -c $< -o $@


all:		$(NAME)

check:	fclean
check:	CFLAGS		+=  -pedantic -ansi
check:	CFLAGS		+=  -fsanitize=address
check:	CFLAGS		+=  -fsanitize=leak
check:	CFLAGS		+=  -fsanitize=undefined
check:	CFLAGS		+=  -g3
check:	LFLAGS		+=  -fsanitize=address
check:	LFLAGS		+=  -fsanitize=leak
check:	LFLAGS		+=  -fsanitize=undefined
check:	LFLAGS		+=  -g3
check:	${NAME}

$(NAME):	$(LIBFT) $(O_DIR) $(OBJS)
			$(CC) $(OBJS) $(CFLAGS) $(LIBFT) -o $@

$(O_DIR):
			$(MKDIR) $(O_DIR)

# ################################## #
#             DEPENDECIES...         #
# ################################## #

$(LIBFT):
			@make -C libft --no-print-directory

# ################################## #
#                CLEAN               #
# ################################## #

clean:
			$(RM) $(O_DIR)
			@make -C libft --no-print-directory

fclean:		clean
			$(RM) $(NAME)
			$(RM) $(LIBFT)

re:			fclean all

-include	$(OBJS:.o=.d)

.PHONY: all check clean fclean re
