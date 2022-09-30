/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 10:15:48 by bschoeff          #+#    #+#             */
/*   Updated: 2022/09/30 09:03:10 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <errno.h>

/* Builtins */
int		bi_pwd(void);
int		bi_env(char **envp);
int		bi_echo(char **args);
int		bi_unset(char **envp);

/* Utils */
char	*get_next_line(int fd);
char	**ft_split(char *str);
char	*ft_strcpy(char *s1, char *s2);

/* Parsing */
void	run_prompt(void);


typedef struct s_fds {
	int		in_pipe[2];
	int		out_pipe[2];
	int		in_fd;
	int		out_fd;
}			t_fds;

typedef struct s_envp
{
	char	**envp;
	int		i;
}				t_envp;

typedef struct s_mini {
	char		**cmd;
	char		*path_cmd;
	char		*path_file;
	t_fds		*fds;
	t_envp		*envp;
	int			in_file;
	int			in_heredoc;
	int			in_pipe;
	int			out_append;
	int			out_trunc;
	int			out_pipe;
	struct s_mini	*next;
}				t_mini;

#endif
