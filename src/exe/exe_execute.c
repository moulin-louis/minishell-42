/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 09:53:11 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/27 14:37:51 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <wait.h>
#include <fcntl.h>

static void	init_pipes(t_cati **mini)
{
	if (pipe((*mini)->fds->pfd_1) == -1 || pipe((*mini)->fds->pfd_2) == -1)
	{
		printf("Catastrophic error when opening pipes, goddbye\n");
		full_exit(mini, 1);
	}
}

void	close_pipes(t_cati **mini)
{
	close((*mini)->fds->pfd_1[0]);
	close((*mini)->fds->pfd_1[1]);
	close((*mini)->fds->pfd_2[0]);
	close((*mini)->fds->pfd_2[1]);
}

int	execute(t_cati **mini)
{
	t_cati	*node;
	int		status;

	node = *mini;
	while (node)
	{
		init_pipes(mini);
		exec_cmd(mini, node);
		close_pipes(mini);
		node = node->next;
	}
	node = *mini;
	while (node)
	{
		if (node->next)
			waitpid(node->pid, &status, 0);
		else
		{
			waitpid(node->fds->last, &status, 0);
			g_status = WEXITSTATUS(status);
		}
		node = node->next;
	}
	return (0);
}
