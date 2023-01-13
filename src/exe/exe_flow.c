/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_flow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:09:59 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/13 12:22:04 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

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

static void	dup_and_close(int node, int std)
{
	dup2(node, std);
	close(node);
}

static void	execve_cmd(t_cati *node, t_cati **mini)
{
	if (node->builtin)
	{
		g_status = exe_bi_launcher(mini, node);
		full_exit(mini, g_status);
	}
	else
	{
		if (!node->path_cmd && !node->outfile && !node->infile)
			ut_cmd_not_found("''");
		else if (node->cmd && node->cmd[0] && node->cmd[0][0] == 0)
			ut_cmd_not_found("''");
		else if (node->cmd)
		{
			if (access(node->path_cmd, R_OK | X_OK) == 0)
				execve(node->path_cmd, node->cmd, node->ev);
			ut_cmd_not_found(node->cmd[0]);
		}
		full_exit(mini, 127);
	}
}

void	exec_cmd(t_cati **mini, t_cati *node)
{
	if (node->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		close(node->fds.pfd[1]);
		set_path_cmd(mini, node);
		if (node->in_file)
			dup_and_close(node->in_fd, STDIN_FILENO);
		else if (node->in_pipe)
			dup_and_close(node->fds.pfd[0], STDIN_FILENO);
		if (node->outfile)
			dup_and_close(node->out_fd, STDOUT_FILENO);
		else if (node->out_pipe)
			dup2(node->next->fds.pfd[1], STDOUT_FILENO);
		close(node->fds.pfd[0]);
		close_all_pipe(node);
		execve_cmd(node, mini);
	}
}

int	exec_node(t_cati **mini, t_cati *node)
{
	node->ev = exe_parse_env(mini);
	if (node->builtin && !node->out_pipe && !node->outfile && !node->in_pipe)
		return (close_pipes(mini), g_status = exe_bi_launcher(mini, node), 1);
	if (set_fds(mini, node) == -1)
		return (-1);
	node->pid = fork();
	g_pid = node->pid;
	if (node->pid == -1)
	{
		ut_putstr_fd("fork :", 2);
		ut_putstr_fd(strerror(errno), 2);
		ut_putstr_fd("\n", 2);
		g_status = errno;
		full_exit(mini, g_status);
	}
	exec_cmd(mini, node);
	clean_split(node->ev);
	node->ev = NULL;
	if (node->in_fd)
		close(node->in_fd);
	if (node->out_fd)
		close(node->out_fd);
	return (0);
}
