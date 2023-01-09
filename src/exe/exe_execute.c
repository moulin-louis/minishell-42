/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foster <foster@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 09:53:11 by bschoeff          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/01/09 16:46:24 by foster           ###   ########.fr       */
=======
/*   Updated: 2023/01/09 16:45:35 by loumouli         ###   ########.fr       */
>>>>>>> b68710790444c7310da59c23b2ecc117c6c53200
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <wait.h>
#include <fcntl.h>

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
		exec_node(mini, node);
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
	return (0);
}
