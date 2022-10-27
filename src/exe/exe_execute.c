/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 09:53:11 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/27 12:27:47 by bschoeff         ###   ########.fr       */
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

int	execute(t_cati **mini)
{
	t_cati	*tmp;
	int		xc_1;
	int		xc_2;

	tmp = *mini;
	while (tmp)
	{
		xc_1 = 0;
		xc_2 = 0;
		init_pipes(mini);
		xc_1 = exec_cmd_1(mini, tmp);
		if (tmp->next)
		{
			tmp = tmp->next;
			xc_2 = exec_cmd_2(mini, tmp);
		}
		tmp = tmp->next;
		if (xc_1)
			waitpid((*mini)->fds->fstchld, &(*mini)->fds->status, 0);
		if (xc_2)
			waitpid((*mini)->fds->scdchld, &(*mini)->fds->status, 0);
		close_pipes(mini);
	}
	return (0);
}
