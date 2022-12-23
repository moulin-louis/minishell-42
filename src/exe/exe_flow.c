/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_flow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foster <foster@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:20:08 by bschoeff          #+#    #+#             */
/*   Updated: 2022/12/23 10:33:11 by foster           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

void	exec_cmd(t_cati **mini, t_cati *node)
{
	if (!node->pid)
	{
		set_path_cmd(mini, node);
		if (node->in_pipe)
		{
			// printf("je lis dans le fds %d\n", node->fds_test->pfd_1[0]);
			dup2(node->fds_test->pfd_1[0], STDIN_FILENO);
		}
		if (node->outfile)
		{
			dup2(node->out_fd, 1);
		}
		else if (node->out_pipe)
		{
			// printf("j'ecris dans le fds %d\n", node->next->fds_test->pfd_1[1]);
			dup2(node->next->fds_test->pfd_1[1], STDOUT_FILENO);
		}
		if (access(node->path_cmd, R_OK | X_OK) == 0)
			execve(node->path_cmd, node->cmd, node->ev);
		printf("command '%s' not found\n", node->cmd[0]);
		full_exit(mini, 127);
	}
}

int	exec_node(t_cati **mini, t_cati *node)
{
	if (node->builtin && !node->out_pipe)
	{
		node->fds->ret = exe_bi_launcher(mini, node);
		return (node->fds->ret);
	}
	node->ev = exe_parse_env(mini);
	if(set_fds(mini, node) == -1)
		return (-1);
	node->pid = fork();
	if (node->pid == -1)
	{
		printf("fork: %s, goodbye\n", strerror(errno));
		g_status = errno;
		full_exit(mini, g_status);
	}
	exec_cmd(mini, node);
	return (0);
}
