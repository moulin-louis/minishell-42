/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:01:04 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/14 16:33:12 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>

void	sig_heredoc(int sig)
{
	(void)sig;
	write(1, "\b\b", 3);
	exit(130);
}

void	sigint_heredoc(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = &sig_heredoc;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
}

/*Read user input and breaf when sep is input*/

int	write_line_infile(char *sep, int fd, t_tok **lst, t_cati **mini)
{
	char	*buffer;

	sigint_heredoc();
	while (1)
	{
		buffer = readline("> ");
		if (ut_strcmp(buffer, sep))
		{
			free(buffer);
			break ;
		}
		write(fd, buffer, ft_strlen(buffer));
		write(fd, "\n", 1);
		free(buffer);
	}
	close(fd);
	env_lstclear(&(*mini)->envp);
	reset_ressources(lst, mini);
	exit (1);
}

int	wait_child(t_cati *node, t_cati **mini, t_tok **lst)
{
	int	status;

	status = 0;
	waitpid(g_var.g_pid, &status, 0);
	if (WIFEXITED(status))
	{
		status = WEXITSTATUS(status);
		if (status == 130)
		{
			reset_ressources(lst, mini);
			g_var.g_status = 130;
			return (1);
		}
	}
	node->infile = ut_strdup("/tmp/heredoc.tmp");
	if (!node->infile)
		ut_clean_parsing_n_quit(mini, lst, errno);
	node->in_file = 1;
	return (0);
}

/*Setup for heredoc, create an infile with user input*/

void	heredoc_redir(t_tok *r_token, t_cati *c_node, t_tok **lst,
			t_cati **mini)
{
	int		fd;

	if (check_compliance_file(r_token->next, lst, mini) == 1)
		return ;
	fd = open("/tmp/heredoc.tmp", O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (!fd)
		ut_clean_parsing_n_quit(mini, lst, errno);
	g_var.g_pid = fork();
	if (g_var.g_pid == 0)
		write_line_infile(r_token->next->str, fd, lst, mini);
	close(fd);
	if (!wait_child(c_node, mini, lst))
		delete_token_redir(r_token, lst);
}
