/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foster <foster@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 09:53:11 by bschoeff          #+#    #+#             */
/*   Updated: 2023/01/06 14:42:41 by foster           ###   ########.fr       */
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
		init_pipes_test(node);
		node = node->next;
	}
	node = *mini;
	//printfmini(*mini);
	while (node)
	{
		exec_node(mini, node);
		close_pipes(&node);
		node = node->next;
	}
	node = *mini;
	while (node)
	{
		// printf("on attend le processur pid : %d", node->pid);
		waitpid(node->pid, &node->fds.status, 0);
		if (node->fds.status == 127)
			g_status = 127;
		// printf(" c'est bon\n");
		node = node->next;
	}
	return (0);
}
