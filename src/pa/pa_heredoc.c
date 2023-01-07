/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:01:04 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/07 21:47:32 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <errno.h>

/*Read user input and breaf when sep is input*/

int	write_line_infile(char *buffer, char *sep, int fd, t_cati *node)
{
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
	node->infile = ut_strdup("/tmp/heredoc.tmp");
	if (!node->infile)
		return (1);
	return (0);
}

/*Setup for heredoc, create an infile with user input*/

void	heredoc_redir(t_tok *r_token, t_cati *c_node, t_tok **lst,
			t_cati **mini)
{
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
	if (!r_token->next || check_compliance_file(r_token->next->str))
	{
		reset_ressources(lst, mini);
		g_status = 2;
		return ;
	}
	fd = open("/tmp/heredoc.tmp", O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (!fd)
		ut_clean_parsing_n_quit(mini, lst, errno);
	if (write_line_infile(buffer, r_token->next->str, fd, c_node))
		ut_clean_parsing_n_quit(mini, lst, errno);
	c_node->in_file = 1;
	close (fd);
	delete_token_redir(r_token, lst);
}
