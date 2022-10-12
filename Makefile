# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/13 11:42:25 by bschoeff          #+#    #+#              #
#    Updated: 2022/10/11 12:05:12 by loumouli         ###   ########.fr        #
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
C_FILES		= minishell.c		\
			  bi_cd.c		\
			  bi_echo.c		\
			  bi_env.c		\
			  bi_exit.c		\
			  bi_export.c	\
			  bi_export2.c	\
			  bi_pwd.c		\
			  bi_unset.c	\
			  cl_clean_all.c	\
			  ev_build_env.c	\
			  ev_build_expt.c	\
			  execute.c		\
			  pa_init_token.c			\
			  pa_main.c			\
			  pa_parse_options.c	\
			  pa_prompt.c		\
			  pa_split_lst_operator.c	\
			  ut_env_list.c		\
			  ut_gnl.c		\
			  ut_mini_list.c	\
			  ut_split_sep.c	\
			  ut_split.c	\
			  ut_strcmp.c	\
			  ut_strcpy.c	\
			  ut_strstuff.c	\
			  ut_token_list.c	\
			  ut_word_len.c	\



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
LFLAGS		=

# ################################## #
#                INCLUDES            #
# ################################## #
CINCLUDES	=	-I ./inc	\
				-I /usr/local/include

CLIBS		=	-L/usr/local/lib -lreadline

# ################################## #
#                RULES               #
# ################################## #

all:	$(NAME)

$(NAME):	$(O_DIR) $(OBJS)
			$(CC) $(OBJS) $(CFLAGS) $(LFLAGS) $(CLIBS) -o $@

$(O_DIR)/%.o: $(C_DIR)/%.c
			$(CC) $(CFLAGS) $(CINCLUDES) -c $< -o $@

$(O_DIR):
			$(MKDIR) $(O_DIR)

check:	fclean
check:	CFLAGS		+=  -pedantic -ansi
check:	CFLAGS		+=  -fsanitize=address
check:	CFLAGS		+=  -fsanitize=leak
check:	CFLAGS		+=  -fsanitize=undefined
check:	CFLAGS		+=  -g3
check:	LFLAGS		+=  -pedantic -ansi
check:	LFLAGS		+=  -fsanitize=address
check:	LFLAGS		+=  -fsanitize=leak
check:	LFLAGS		+=  -fsanitize=undefined
check:	LFLAGS		+=  -g3
check:	${NAME}

# ################################## #
#                CLEAN               #
# ################################## #

clean:
			$(RM) $(O_DIR)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

-include	$(OBJS:.o=.d)

.PHONY: all check clean fclean re
