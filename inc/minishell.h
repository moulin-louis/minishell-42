/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 10:15:48 by bschoeff          #+#    #+#             */
/*   Updated: 2022/09/29 14:41:25 by loumouli         ###   ########.fr       */
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

/* Builtins bi_*.c */
int		bi_pwd(void);
int		bi_env(char **envp);
int		bi_echo(char **args);
int		bi_unset(char **envp);

/*runing prompt*/
void	run_prompt(void);

/*files for utils fn*/
char	*get_next_line(int fd);

typedef struct s_fds {
	int	x;
}			t_fds;

typedef struct s_envp
{
	char	**envp;
	int		i;
}				t_envp;

typedef struct s_mini {
	char	**cmd;
	char	*path_cmd;
	char	*path_file;
	t_fds	*fds;
	t_envp	*envp;
	int		in_file;
	int		in_heredoc;
	int		in_pipe;
	int		out_append;
	int		out_trunc;
	int		out_pipe;
	t_mini	*next;
}				t_mini;
#endif
