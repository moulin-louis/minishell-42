/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:01:04 by loumouli          #+#    #+#             */
/*   Updated: 2022/10/24 14:07:34 by loumouli         ###   ########.fr       */
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

void	write_line_infile(char *buffer, char *sep, int fd)
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
}

void	heredoc_redir(t_tok **lst, t_tok *dest, t_cati *node, t_cati **mini)
{
	char	*sep;
	int		fd;
	char	*buffer;
	t_tok	*temp;

	temp = 0;
	buffer = NULL;
	sep = dest->next->str;
	fd = open("/tmp/.heredoc.tmp", O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (!fd)
	{
		perror("tmp heredoc :");
		clean_tok(lst);
		full_exit(mini, errno);
	}
	write_line_infile(buffer, sep, fd);
	node->infile = ut_strdup("/tmp/.heredoc.tmp");
	if (!node->infile)
		ut_clean_parsing_n_quit(mini, lst, errno);
	node->in_file = 1;
	close (fd);
	if (ut_strcmp((*lst)->str, dest->str))
		clean_lst_mode(dest, temp, lst, 1);
	else
		clean_lst_mode(dest, temp, lst, 2);
}
