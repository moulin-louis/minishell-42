/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 09:53:11 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/26 15:29:43 by bschoeff         ###   ########.fr       */
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

static void	close_pipes(t_cati **mini)
{
	close((*mini)->fds->pfd_1[0]);
	close((*mini)->fds->pfd_1[1]);
	close((*mini)->fds->pfd_2[0]);
	close((*mini)->fds->pfd_2[1]);
}

static int	exec_node(t_cati **mini, t_cati *node)
{
	if (!node->out_pipe)
		return (exec_cmd(mini, node));
	return (0);
}

int	execute(t_cati **mini)
{
	t_cati	*tmp;

	tmp = *mini;
	while (tmp)
	{
		init_pipes(mini);
		exec_node(mini, tmp);
		if (tmp->next)
		{
			tmp = tmp->next;
			exec_node(mini, tmp);
		}
		tmp = tmp->next;
		close_pipes(mini);
	}
	return (0);
}
