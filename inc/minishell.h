/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 10:15:04 by                   #+#    #+#             */
/*   Updated: 2022/10/09 15:46:23 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_fds {
	int		in_pipe[2];
	int		out_pipe[2];
	int		in_fd;
	int		out_fd;
	int		status;
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
int		bi_exit(t_cati **mini);
int		bi_export(t_cati **mini);
int		bi_expt_expt(t_cati **mini, char *str, int flag);
int		bi_expt_env(t_cati **mini, char *str);
int		bi_pwd(t_cati **mini);
int		bi_unset(t_cati **mini);

/* Utils */
char	*ut_gnl(int fd);
char	**ut_split(char *str);
int		ut_strcmp(char *s1, char *s2);
char	*ut_strcpy(char *s2);
int		ut_word_len(char *str);
void	env_lstaddback(t_envp **envp, t_envp *new);
void	env_lstclear(t_envp **envp);
void	env_lstdelone(t_envp **envp, t_envp *tmp);
t_cati	*mini_lstnew(char *str);
void	mini_lstaddback(t_cati **mini, t_cati *node);
void	mini_delone(t_cati	*node);
int		ft_strlen(char *str);
char	*ut_strdup(char *str);
int		ft_strncmp(const char *s1, const char *s2, int n);
void	ft_bzero(void *s, int n);

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
t_cati	*tokenize_string(char *str);

#endif
