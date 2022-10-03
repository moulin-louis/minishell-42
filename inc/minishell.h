/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 10:15:48 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/03 15:18:12 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_fds {
	int		in_pipe[2];
	int		out_pipe[2];
	int		in_fd;
	int		out_fd;
}			t_fds;

typedef struct s_envp
{
	char			*var;
	int				place;
	int				length;
	struct s_envp	*next;
}				t_envp;

typedef struct s_mini {
	char			**cmd;
	int				builtin;
	char			*path_cmd;
	char			*path_file;
	t_fds			*fds;
	t_envp			*envp;
	int				in_file;
	int				in_heredoc;
	int				in_pipe;
	int				out_append;
	int				out_trunc;
	int				out_pipe;
	struct s_mini	*next;
}				t_mini;

/* Builtins */
int		bi_pwd(void);
int		bi_env(t_envp **envp);
int		bi_echo(char **args);
int		bi_unset(t_envp **envp, char *var);

/* Utils */
char	*get_next_line(int fd);
char	**ft_split(char *str);
char	*ft_strcpy(char *s2);
int		word_len(char *str);
void	lstaddback(t_envp **envp, t_envp *new);
void	lstclear(t_envp **envp);

/* Environment */
int		ev_build_env(char **env, t_envp **envp);

/* Cleanup */
void	clean_split(char **arr);
void	clean_env(t_envp **envp);

/* Parsing */
void	run_prompt(void);

#endif
