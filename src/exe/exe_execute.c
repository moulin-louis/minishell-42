/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 09:53:11 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/24 14:20:47 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <wait.h>
#include <fcntl.h>

static void	close_pipes(t_cati **mini)
{
	if ((*mini)->fds->pfd_1[0])
		close((*mini)->fds->pfd_1[0]);
	if ((*mini)->fds->pfd_1[1])
		close((*mini)->fds->pfd_1[1]);
	if ((*mini)->fds->pfd_2[0])
		close((*mini)->fds->pfd_2[0]);
	if ((*mini)->fds->pfd_2[1])
		close((*mini)->fds->pfd_2[1]);
}

static void	reset_chcks(t_cati **mini)
{
	(*mini)->fds->chkfst = 0;
	(*mini)->fds->chkscd = 0;
}

int	execute(t_cati **mini)
{
	t_cati	*tmp;

	tmp = *mini;
	while (tmp)
	{
		reset_chcks(mini);
		if (pipe(tmp->fds->pfd_1) == -1)
			full_exit(mini, errno);
		(*mini)->fds->chkfst = first_fork(mini, tmp);
		if (tmp->next)
		{
			tmp = tmp->next;
			if (pipe(tmp->fds->pfd_2) == -1)
				full_exit(mini, errno);
			dup2((*mini)->fds->pfd_2[0], (*mini)->fds->pfd_1[1]);
			(*mini)->fds->chkscd = second_fork(mini, tmp);
		}
		if ((*mini)->fds->chkfst)
			waitpid(tmp->fds->frst, &tmp->fds->status, 0);
		if ((*mini)->fds->chkscd)
			waitpid(tmp->fds->scnd, &tmp->fds->status, 0);
		tmp = tmp->next;
	}
	close_pipes(mini);
	return (0);
}
