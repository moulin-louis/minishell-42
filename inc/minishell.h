/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 10:15:04 by                   #+#    #+#             */
/*   Updated: 2022/10/21 11:14:29 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>

typedef struct s_fds {
	int		pfd[2];
	int		in_fd;
	int		out_fd;
	pid_t	frst;
	pid_t	scnd;
	int		status;
	int		ret;
}			t_fds;

typedef struct s_envp
{
	char			**var;
	struct s_envp	*next;
}				t_envp;

typedef struct s_cati {
	char			**cmd;
	char			**ev;
	char			*path_cmd;
	char			*infile;
	char			*outfile;
	t_fds			*fds;
	t_envp			*envp;
	int				builtin;
	int				in_file;
	int				in_pipe;
	int				out_pipe;
	int				out_append;
	int				out_trunc;
	struct s_cati	*next;
}				t_cati;

typedef struct s_tok {
	char			*str;
	struct s_tok	*next;
}				t_tok;

/* Builtins */
int		bi_cd(t_cati *node);
int		bi_echo(t_cati *node);
int		bi_env(t_cati **mini);
int		bi_exit(t_cati **mini, t_cati *node);
int		bi_export(t_cati *node);
int		bi_pwd(t_cati *node);
int		bi_unset(t_cati **mini, t_cati *node);

/* Utils */
void	*ut_calloc(int nb, int sz);
char	*ut_gnl(int fd);
char	**ut_split(char *str);
int		ut_strcmp(char *s1, char *s2);
char	*ut_strcpy(char *s2);
char	*ut_strjoin(char *s1, char *s2);
int		ut_word_len(char *str);
int		ft_strlen(char *str);
char	*ut_strdup(char *str);
int		ft_strncmp(const char *s1, const char *s2, int n);
void	ft_bzero(void *s, int n);
char	**extract_sep(char *str);
int		ut_within_long(char *str);

/* linked list utils and function */
/*env utils*/
void	env_lstaddback(t_envp **envp, t_envp *new);
void	env_lstclear(t_envp **envp);
void	env_lstdelone(t_envp **envp, t_envp *tmp);
int		env_lstsize(t_envp **envp);

/*mini utils*/
t_cati	*mini_lstnew(void);
void	mini_lstaddback(t_cati **mini, t_cati *node);
t_cati	*mini_lstlast(t_cati *mini);

/*tok utils*/
int		tok_len(t_tok *lst);
void	tok_delone(t_tok *node);
void	tok_addback(t_tok **lst, t_tok *node);
t_tok	*tok_new(char *str);
void	clean_tok(t_tok **lst);

/* Environment */
int		ev_build_env(char **env, t_envp **envp);
char	**ut_env_split(char *str);
int		set_new1(t_envp *new1);
int		set_new2(t_envp *new2);
int		set_new3(t_envp *new3);
int		change_content(t_cati *node, char *str);
int		do_the_expt(t_cati *node, char *str);

/* Cleanup */
void	clean_split(char **arr);
void	clean_mini(t_cati **mini);
void	error_exit(t_cati **mini, int i);

/* Parsing */
void	run_prompt(t_envp *envp, t_fds *fds);
void	parsing(char *input, t_cati **mini);
t_tok	*init_token_list(char *str);
void	split_lst_operator(t_tok *lst);
void	setup_redirection(t_tok **lst, t_cati *mini);
void	parse_options(t_tok **lst, t_cati **mini);

/*redirection in parsing*/
void	clean_lst_mode(t_tok *dest, t_tok *temp, t_tok **lst, int i);
void	in_redir(t_tok **lst, t_tok *dest, t_cati *mini);
void	out_redir(t_tok **lst, t_tok *dest, t_cati *mini);
void	append_redir(t_tok **lst, t_tok *dest, t_cati *mini);
void	heredoc_redir(t_tok **lst, t_tok *dest, t_cati *mini);

/* Execute */
int		execute(t_cati **mini);
int		exe_bi_launcher(t_cati **mini, t_cati *node);
char	**exe_parse_env(t_cati **mini);
void	exe_child(t_cati **mini, t_cati *node);

/* UTILITAIRE TEMP */
void	printfmini(t_cati *mini);
#endif
