/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foster <foster@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 09:53:11 by bschoeff          #+#    #+#             */
/*   Updated: 2022/12/23 10:32:41 by foster           ###   ########.fr       */
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
	if (pipe(node->fds_test->pfd_1) == -1)
	{
		printf("Catastrophic error when opening pipes, goddbye\n");
	}
}

void	close_pipes(t_cati **mini)
{
	close((*mini)->fds->pfd_1[0]);
	close((*mini)->fds->pfd_1[1]);
}

int	execute(t_cati **mini)
{
	t_cati	*node;

	node = *mini;
	while (node)
	{
		init_pipes_test(node);
		node = node->next;
	}
	node = *mini;
	while (node)
	{
		exec_node(mini, node);
		node = node->next;
	}
	node = *mini;
	while (node)
	{
		// printf("on attend le processur pid : %d", node->pid);
		waitpid(node->pid, &node->fds_test->status, 0);
		// printf(" c'est bon\n");
		node = node->next;
	}
	node = *mini;
	while (node)
	{
		close(node->fds_test->pfd_1[0]);
		close(node->fds_test->pfd_1[1]);
		node = node->next;
	}
	return (0);
}
