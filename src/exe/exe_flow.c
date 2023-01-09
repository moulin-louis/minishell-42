/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_flow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foster <foster@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:20:08 by bschoeff          #+#    #+#             */
/*   Updated: 2023/01/09 15:01:23 by foster           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

static void	close_all_pipe(t_cati *node)
{
	if (node->in_fd)
			close(node->in_fd);
	if (node->out_fd)
			close(node->out_fd);
	node = node->next;
	while (node)
	{
		close(node->fds.pfd[0]);
		close(node->fds.pfd[1]);
		node = node->next;
	}
}

static void execve_cmd(t_cati *node, t_cati **mini)
{
	int	access_auth;
	if (!node->path_cmd && !node->outfile && !node->infile)
		printf("Command '' not found\n");
	else
	{
		access_auth = access(node->path_cmd, R_OK | X_OK) == 0;
		if (access_auth)
			execve(node->path_cmd, node->cmd, node->ev);
		perror("shellnado");
		full_exit(mini, 127);
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
		close_all_pipe(node);
		execve_cmd(node, mini);
	}
	else
	{
		clean_split(node->ev);
		node->ev = NULL;
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
		close_pipes(mini);
		node->fds.ret = exe_bi_launcher(mini, node);
		return (node->fds.ret);
	}
	node->ev = exe_parse_env(mini);
	if (set_fds(mini, node) == -1)
		return (-1);
	node->pid = fork();
	g_pid = node->pid;
	if (node->pid == -1)
	{
		printf("fork: %s, goodbye\n", strerror(errno));
		g_status = errno;
		full_exit(mini, g_status);
	}
	exec_cmd(mini, node);
	return (0);
}
