/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:20:54 by bschoeff          #+#    #+#             */
/*   Updated: 2023/01/13 12:15:27 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/stat.h>

extern int	g_status;
extern int	g_pid;

typedef struct s_fds
{
	int		pfd[2];
	int		ret;
	int		status;
}		t_fds;

typedef struct s_envp
{
	char			**var;
	struct s_envp	*next;
}				t_envp;

typedef struct s_cati
{
	char			**cmd;
	char			**ev;
	char			*path_cmd;
	char			*infile;
	char			*outfile;
	t_fds			fds;
	t_envp			*envp;
	int				builtin;
	int				in_fd;
	int				out_fd;
	int				in_file;
	int				in_pipe;
	int				out_pipe;
	int				out_append;
	int				out_trunc;
	struct stat		buff;
	pid_t			pid;
	struct s_cati	*next;
}				t_cati;

typedef struct s_tok
{
	char			*str;
	struct s_tok	*next;
}				t_tok;

/* BUILTINS */
int		bi_cd(t_cati **mini, t_cati *node);
int		cd_home(t_cati **mini);
int		bi_echo(t_cati *node);
int		bi_env(t_cati **mini);
int		bi_exit(t_cati **mini, t_cati *node);
int		bi_export(t_cati *node);
int		bi_pwd(t_cati *node);
int		bi_unset(t_cati **mini, t_cati *node);



/* PARSING */
/*signal*/
void	setup_sig(void);
void	run_prompt(t_envp *envp, t_fds *fds);
void	parsing(char *input, t_cati **mini);
/*tokenomization*/
t_tok	*init_token_list(char *str, t_cati **mini);
void	split_token(const char *str, int *i, t_tok **lst, t_cati **mini);
void	split_lst_operator(t_tok **lst, t_cati **mini);
char	**split_tok(const char *str, int nbr_tok, t_tok **lst, t_cati **mini);
/*expand stuff*/
void	expand_lst(t_tok **lst, t_cati **mini);
int		find_len(char *str, int i);
void	clean_quote(t_tok **lst, t_cati **mini);
/*check error in syntax*/
void	check_pipe_token(t_tok **lst, t_cati **mini);
void	check_double_redirection(t_tok **lst, t_cati **mini);
/*parse option and redirection*/
void	parse_options(t_tok **lst, t_cati **mini);
void	setup_redirection(t_tok **lst, t_cati *node, t_cati **mini);
/*setup pipe, env and builtin for mini list*/
void	fill_node_of_pipe(t_cati *mini);
void	fill_node_env(t_cati *mini);
void	check_builtin(t_cati *mini);
/*error handling parsing*/
void	reset_ressources(t_tok **lst, t_cati **mini);
void	trigger_error(t_tok **lst, t_cati **mini, char *str);
void	ut_clean_parsing_n_quit(t_cati **mini, t_tok **lst, int error);
/*redirection in parsing*/
void	in_redir(t_tok *r_token, t_cati *c_node, t_tok **lst, t_cati **mini);
void	out_redir(t_tok *r_token, t_cati *c_node, t_tok **lst, t_cati **mini);
void	app_redir(t_tok *r_token, t_cati *c_node, t_tok **lst, t_cati **mini);
void	heredoc_redir(t_tok *r_token, t_cati *c_node, t_tok **lst,
			t_cati **mini);
void	delete_token_redir(t_tok *node, t_tok **lst);
int		check_compliance_file(t_tok *node, t_tok **lst, t_cati **mini);
void	check_file(char *str, t_cati *node, t_tok **lst, t_cati **mini);

/* EXECUTE */
int		execute(t_cati **mini);
void	close_pipes(t_cati **mini);
int		set_fds(t_cati **mini, t_cati *node);
int		exec_node(t_cati **mini, t_cati *node);
void	exec_cmd(t_cati **mini, t_cati *node);
int		exe_bi_launcher(t_cati **mini, t_cati *node);
char	**exe_parse_env(t_cati **mini);
void	set_path_cmd(t_cati **mini, t_cati *node);

/* UTILS */
void	ut_bzero(void *s, int n);
void	*ut_calloc(int nb, int sz);
int		ft_isnum(char c);
int		ft_isalpha(char c);
char	*ut_itoa(int n);
void	ut_putstr_fd(char *s, int fd);
void	ut_cmd_not_found(char *s);
char	**ut_split_char(const char *str, char c);
int		ut_strcmp(char *s1, char *s2);
char	*ut_strcpy(char *s2);
char	*ut_strinsert(const char *og, char *target, const char *payload);
char	*ut_strjoin(char *s1, char *s2);
int		ft_strlen(const char *str);
char	*ut_strdup(char *str);
int		ft_strncmp(const char *s1, const char *s2, int n);
int		ut_within_long(char *str);
/* linked list utils and function */
/*env utils*/
void	env_lstaddback(t_envp **envp, t_envp *new);
void	env_lstclear(t_envp **envp);
void	env_lstdelone(t_envp **envp, t_envp *tmp);
int		env_lstsize(t_envp **envp);
void	env_delone(t_envp *node);
/*mini utils*/
t_cati	*mini_lstnew(void);
void	mini_lstaddback(t_cati **mini, t_cati *node);
t_cati	*mini_lstlast(t_cati *mini);
void	ft_create_node(t_cati **mini, t_envp *envp, t_fds *fds);
/*tok utils*/
void	tok_delone(t_tok *node);
void	tok_addback(t_tok **lst, t_tok *node);
t_tok	*tok_new(char *str);
void	clean_tok(t_tok **lst);

/* ENVIRONEMENTS */
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
void	full_exit(t_cati **mini, int i);
void	reset_ressources(t_tok **lst, t_cati **mini);

#endif
