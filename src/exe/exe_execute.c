/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foster <foster@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 09:53:11 by bschoeff          #+#    #+#             */
/*   Updated: 2022/12/23 13:58:29 by foster           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <wait.h>
#include <fcntl.h>



static void	init_pipes_test(t_cati *node)
{
	t_fds	*fds = malloc(sizeof(t_fds));
	node->fds_test = fds;
	if (pipe(node->fds_test->pfd) == -1)
	{
		printf("Catastrophic error when opening pipes, goddbye\n");
	}
}

void	close_pipes(t_cati **mini)
{
	close((*mini)->fds->pfd[0]);
	close((*mini)->fds->pfd[1]);
}

int	execute(t_cati **mini)
{
	t_cati	*node;
	t_cati *cpy;

	node = *mini;
	while (node)
	{
		init_pipes_test(node);
		node = node->next;
	}
	node = *mini;
	printfmini(*mini);
	while (node)
	{
		exec_node(mini, node);
		node = node->next;
	}
	node = *mini;
	while (node)
	{
		if(!node->next)
		{
			cpy = *mini;
			while (cpy)
			{
				if (cpy->fds->pfd[0])
				{
					close(cpy->fds_test->pfd[0]);
				}
				if (cpy->fds->pfd[1])
				{
					close(cpy->fds_test->pfd[1]);
				}
				cpy = cpy->next;
			}
		}
		waitpid(node->pid, &node->fds_test->status, 0);
		node = node->next;
	}
	return (0);
}
