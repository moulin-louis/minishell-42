/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:01:04 by loumouli          #+#    #+#             */
/*   Updated: 2022/12/14 12:36:48 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/*Read user input and breaf when sep is input*/

void	write_line_infile(char *buffer, char *sep, int fd)
{
	while (1)
	{
		buffer = readline("> ");
		if (ut_strcmp(buffer, sep))
		{
			free(buffer);
			return ;
		}
		write(fd, buffer, ft_strlen(buffer));
		write(fd, "\n", 1);
		free(buffer);
	}
}

/*Setup for heredoc, create an infile with user input*/

void	heredoc_redir(t_tok *r_token, t_cati *c_node, t_tok **lst,
			t_cati **mini)
{
	//char	*sep;
	int		fd;
	char	*buffer;

	buffer = NULL;
	if (!r_token->next)
	{
		printf("shellnado : invalid token syntax near '\\n'\n");
		reset_ressources(lst, mini);
		g_status = 2;
		return ;
	}
	//sep = r_token->next->str;
	if (!r_token->next || check_compliance_file(r_token->next->str))
	{
		reset_ressources(lst, mini);
		g_status = 2;
		return ;
	}
	fd = open("/tmp/heredoc.tmp", O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (!fd)
		ut_clean_parsing_n_quit(mini, lst, errno);
	write_line_infile(buffer, r_token->next->str, fd);
	c_node->infile = ut_strdup("/tmp/heredoc.tmp");
	if (!c_node->infile)
		ut_clean_parsing_n_quit(mini, lst, errno);
	c_node->in_file = 1;
	close (fd);
	delete_token_redir(r_token, lst);
}
