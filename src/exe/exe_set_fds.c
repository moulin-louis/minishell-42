/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_set_fds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foster <foster@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 13:14:07 by bschoeff          #+#    #+#             */
/*   Updated: 2023/01/09 14:13:50 by foster           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

static void	set_out_fd(t_cati **mini, t_cati *node)
{
	stat(node->outfile, &node->buff);
	if (S_ISDIR(node->buff.st_mode))
	{
		printf("%s: Is a directory\n", node->outfile);
		full_exit(mini, 127);
	}
	if (node->out_trunc)
	{
		node->out_fd = open(node->outfile, O_WRONLY | O_CREAT, 0644);
		if (node->out_fd == -1)
		{
			perror(node->outfile);
			full_exit(mini, errno);
		}
	}
	if (node->out_append)
	{
		node->out_fd = open(node->outfile, O_APPEND | O_CREAT, 0644);
		if (node->out_fd == -1)
		{
			perror(node->outfile);
			full_exit(mini, errno);
		}
	}
}

int	set_fds(t_cati **mini, t_cati *node)
{
	if (node->in_file)
	{
		stat(node->infile, &node->buff);
		if (S_ISDIR(node->buff.st_mode))
		{
			printf("%s: Is a directory\n", node->infile);
			return (-1);
		}
		node->in_fd = open(node->infile, O_RDONLY);
		if (node->in_fd == -1)
		{
			printf("shellnado: %s: Is not a file or directory\n", node->infile);
			return (-1);
		}
	}
	if (node->outfile)
		set_out_fd(mini, node);
	return (0);
}
