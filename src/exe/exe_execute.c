/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 09:53:11 by bschoeff          #+#    #+#             */
/*   Updated: 2023/01/13 12:21:30 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <wait.h>

void	init_pipes(t_cati *node, t_cati **mini)
{
	t_cati		*mini_cpy;

	if (pipe(node->fds.pfd) == -1)
	{
		perror("Catastrophic error when opening pipes, goddbye\n");
		mini_cpy = *mini;
		while (mini_cpy && (mini_cpy) != node)
		{
			close_pipes(&mini_cpy);
			(mini_cpy) = (mini_cpy)->next;
		}
		full_exit(mini, errno);
	}
}

void	close_pipes(t_cati **mini)
{
	close((*mini)->fds.pfd[0]);
	close((*mini)->fds.pfd[1]);
}

int	execute(t_cati **mini)
{
	t_cati	*node;

	node = *mini;
	while (node)
	{
		init_pipes(node, mini);
		node = node->next;
	}
	node = *mini;
	while (node)
	{
		if (exec_node(mini, node))
			return (0);
		close_pipes(&node);
		node = node->next;
	}
	node = *mini;
	while (node)
	{
		waitpid(node->pid, &node->fds.status, 0);
		if (!node->next)
			g_status = WEXITSTATUS(node->fds.status);
		node = node->next;
	}
	return (g_pid = 1, 0);
}
