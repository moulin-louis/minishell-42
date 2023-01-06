/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_flow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foster <foster@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:20:08 by bschoeff          #+#    #+#             */
/*   Updated: 2023/01/06 17:13:33 by foster           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

static void close_all_pipe(t_cati *node)
{
	while (node)
	{
		close(node->fds.pfd[0]);
		close(node->fds.pfd[1]);
		node = node->next;
	}
}

void	exec_cmd(t_cati **mini, t_cati *node)
{
	if (node->pid == 0)
	{
		close(node->fds.pfd[1]);
		set_path_cmd(mini, node);
		if (node->in_file)
		{
			dup2(node->in_fd, STDIN_FILENO);
			close(node->in_fd);
		}
		else if (node->in_pipe)
		{
			dup2(node->fds.pfd[0], STDIN_FILENO);
			close(node->fds.pfd[0]);
		}
		if (node->outfile)
		{
			dup2(node->out_fd, STDOUT_FILENO);
			close(node->out_fd);
		}
		else if (node->out_pipe)
			dup2(node->next->fds.pfd[1], STDOUT_FILENO);
		close(node->fds.pfd[0]);



		if (node->in_fd)
			close(node->in_fd);
		if (node->out_fd)
			close(node->out_fd);
		close_all_pipe(node->next);
		if (access(node->path_cmd, R_OK | X_OK) == 0)
			execve(node->path_cmd, node->cmd, node->ev);
		printf("command '%s' not found\n", node->cmd[0]);
		full_exit(mini, 127);
	}
	else
	{
		if (node->in_fd)
			close(node->in_fd);
		if (node->out_fd)
			close(node->out_fd);
	}
}

int	exec_node(t_cati **mini, t_cati *node)
{
	if (node->builtin && !node->out_pipe)
	{
		node->fds.ret = exe_bi_launcher(mini, node);
		return (node->fds.ret);
	}
	node->ev = exe_parse_env(mini);
	if(set_fds(mini, node) == -1)
		return (-1);
	node->pid = fork();
	g_pid = node->pid;
	if (node->pid == -1)
	{
		printf("fork: %s, goodbye\n", strerror(errno));
		g_status = errno;
		full_exit(mini, g_status);
	}
	printf("fds.pfd[0] = %d, fds.pfd[1] = %d\n", node->fds.pfd[0], node->fds.pfd[1]);
	exec_cmd(mini, node);
	return (0);
}
