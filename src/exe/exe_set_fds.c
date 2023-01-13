/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_set_fds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 13:14:07 by bschoeff          #+#    #+#             */
/*   Updated: 2023/01/13 12:22:46 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

static void	set_out_fd(t_cati **mini, t_cati *node)
{
	stat(node->outfile, &node->buff);
	if (S_ISDIR(node->buff.st_mode))
	{
		ut_putstr_fd(node->outfile, 2);
		ut_putstr_fd(": Is a directory\n", 2);
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
			ut_putstr_fd(node->infile, 2);
			ut_putstr_fd(": Is a directory\n", 2);
			return (-1);
		}
		node->in_fd = open(node->infile, O_RDONLY);
		if (node->in_fd == -1)
		{
			ut_putstr_fd("bash: ", 2);
			ut_putstr_fd(node->infile, 2);
			ut_putstr_fd(": Is not a file or directory\n", 2);
			return (-1);
		}
	}
	if (node->outfile)
		set_out_fd(mini, node);
	return (0);
}
