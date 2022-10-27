# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: loumouli < loumouli@student.42.fr >        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/13 11:42:25 by bschoeff          #+#    #+#              #
#    Updated: 2022/10/27 19:57:20 by loumouli         ###   ########.fr        #
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
C_FILES		= minishell.c					\
			  bi/bi_cd.c					\
			  bi/bi_echo.c					\
			  bi/bi_env.c					\
			  bi/bi_exit.c					\
			  bi/bi_exit2.c					\
			  bi/bi_export.c				\
			  bi/bi_export2.c				\
			  bi/bi_pwd.c					\
			  bi/bi_unset.c					\
			  ev/ev_build_env.c				\
			  ev/ev_build_env2.c			\
			  exe/exe_execute.c				\
			  exe/exe_flow.c				\
			  exe/exe_launcher.c			\
			  exe/exe_parse_env.c			\
			  exe/exe_set_fds.c				\
			  exe/exe_set_path_cmd.c		\
			  pa/pa_expand.c				\
			  pa/pa_heredoc.c				\
			  pa/pa_init_token.c			\
			  pa/pa_main.c					\
			  pa/pa_parse_options.c			\
			  pa/pa_prompt.c				\
			  pa/pa_redirections.c			\
			  pa/pa_setup_redir.c			\
			  pa/pa_split_lst_operator.c	\
			  ut/ut_calloc.c				\
			  ut/ut_clean_all.c				\
			  ut/ut_env_list.c				\
			  ut/ut_env_split.c				\
			  ut/ut_extract_sep.c			\
			  ut/ut_gnl.c					\
			  ut/ut_itoa.c					\
			  ut/ut_mini_list.c				\
			  ut/ut_split_char.c			\
			  ut/ut_split.c					\
			  ut/ut_strcmp.c				\
			  ut/ut_strcpy.c				\
			  ut/ut_strjoin.c				\
			  ut/ut_strstuff.c				\
			  ut/ut_token_list.c			\
			  ut/ut_word_len.c				\

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
			$(MKDIR) $(O_DIR)/bi
			$(MKDIR) $(O_DIR)/ev
			$(MKDIR) $(O_DIR)/exe
			$(MKDIR) $(O_DIR)/pa
			$(MKDIR) $(O_DIR)/ut

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
-include ./objs/*.d
-include ./objs/bi/*.d
-include ./objs/ev/*.d
-include ./objs/exe/*.d
-include ./objs/pa/*.d
-include ./objs/ut/*.d

.PHONY: all check clean fclean re
