/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 09:53:11 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/21 16:44:28 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <wait.h>
#include <fcntl.h>

int	execute(t_cati **mini)
{
	t_cati	*tmp;

	tmp = *mini;
	while (tmp)
	{
		if (pipe(tmp->fds->pfd) == -1)
			error_exit(mini, errno);
		if (tmp->builtin && !tmp->out_pipe)
			exe_bi_launcher(mini, tmp);
		else
		{
			tmp->fds->frst = fork();
			if (tmp->fds->frst == -1)
				error_exit(mini, errno);
			if (!tmp->fds->frst)
				exe_child(mini, tmp);
			if (tmp->next)
			{
				tmp = tmp->next;
				if (tmp->builtin && !tmp->out_pipe)
					exe_bi_launcher(mini, tmp);
				else
				{
					dup2(tmp->fds->pfd[0], tmp->fds->pfd[1]);
					tmp->fds->scnd = fork();
					if (tmp->fds->scnd == -1)
						error_exit(mini, errno);
					if (!tmp->fds->scnd)
						exe_child(mini, tmp);
				}
			}
			waitpid(tmp->fds->frst, &tmp->fds->status, 0);
			waitpid(tmp->fds->scnd, &tmp->fds->status, 0);
		}
		tmp =tmp->next;
	}
	close((*mini)->fds->pfd[0]);
	close((*mini)->fds->pfd[1]);
	return (0);
}
