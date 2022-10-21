/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_children.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 08:23:18 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/21 12:14:38 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>

static void	set_execv(t_cati **mini, t_cati *node)
{
	if (!access(node->path_cmd, R_OK || X_OK))
	{
		perror("shellnado:");
		error_exit(mini, errno);
	}
}

static void	set_elements(t_cati *node)
{
	if (node->infile)
	{
		close(node->fds->pfd[0]);
		dup2(node->fds->in_fd, 0);
	}
	if (!node->next && !node->outfile)
		close(node->fds->pfd[1]);
	if (node->outfile)
		dup2(node->fds->out_fd, 1);
	if (node->in_pipe)
		dup2(node->fds->pfd[0], 0);
	if (node->out_pipe)
		dup2(node->fds->pfd[1], 1);
}

void	exe_child(t_cati **mini, t_cati *node)
{
	node->ev = exe_parse_env(mini);
	set_elements(node);
	if (!node->builtin)
	{
		set_execv(mini, node);
		execve(node->path_cmd, node->cmd, node->ev);
	}
	else
		error_exit(mini, exe_bi_launcher(mini, node));
	clean_mini(mini);
}
