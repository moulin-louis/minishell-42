/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 09:53:11 by bschoeff          #+#    #+#             */
/*   Updated: 2023/01/08 16:30:18 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <wait.h>
#include <fcntl.h>

void	init_pipes(t_cati *node)
{
	if (pipe(node->fds.pfd) == -1)
	{
		printf("Catastrophic error when opening pipes, goddbye\n");
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
		init_pipes(node);
		node = node->next;
	}
	node = *mini;
	while (node)
	{
		exec_node(mini, node);
		close_pipes(&node);
		node = node->next;
	}
	node = *mini;
	while (node)
	{
		waitpid(node->pid, &node->fds.status, 0);
		if (node->fds.status == 127)
			g_status = 127;
		node = node->next;
	}
	return (0);
}
