/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 10:15:48 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/06 12:20:56 by bschoeff         ###   ########.fr       */
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
	struct s_envp	*next;
}				t_envp;

typedef struct s_cati {
	char			**cmd;
	int				builtin;
	char			*path_cmd;
	char			*path_file;
	t_fds			*fds;
	t_envp			*envp;
	t_envp			*expt_ev;
	int				in_file;
	int				in_heredoc;
	int				in_pipe;
	int				out_append;
	int				out_trunc;
	int				out_pipe;
	int				ret;
	struct s_cati	*next;
}				t_cati;

/* Builtins */
int		bi_cd(t_cati **mini);
int		bi_echo(t_cati **mini);
int		bi_env(t_cati **mini);
int		bi_export(t_cati **mini);
int		bi_pwd(t_cati **mini);
int		bi_unset(t_cati **mini);

/* Utils */
char	*ut_gnl(int fd);
char	**ut_split(char *str);
char	*ut_strcpy(char *s2);
int		ut_word_len(char *str);
void	env_lstaddback(t_envp **envp, t_envp *new);
void	env_lstclear(t_envp **envp);

/* Environment */
int		ev_build_env(char **env, t_envp **envp);
int		ev_build_expt(char **env, t_envp **envp);

/* Cleanup */
void	clean_split(char **arr);
void	clean_env(t_envp **envp);
void	clean_mini(t_cati **mini);

/* Parsing */
void	run_prompt(void);
void	parsing(char *input);

#endif
