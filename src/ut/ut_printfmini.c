/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_printfmini.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 11:57:44 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/06 13:53:40 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

/*Print all node from t_cati list*/

void	printfmini(t_cati *mini)
{
	int		i;
	t_cati	*tmp;

	tmp = mini;
	while (tmp)
	{
		printf("path_cmd = %s\n", tmp->path_cmd);
		if (tmp->cmd)
		{
			i = -1;
			while (tmp->cmd[++i])
				printf("cmd[%d] = [%s]\t", i, tmp->cmd[i]);
			printf("\n");
		}
		printf("infile = %s\noutfile = %s\n", tmp->infile, tmp->outfile);
		printf("in_fd = %d\nout_fd = %d\n", tmp->in_fd, tmp->out_fd);
		printf("fds = %p\nenvp = %p\n", & tmp->fds, & tmp->envp);
		printf("builtin = %d\nin_file = %d\n", tmp->builtin, tmp->in_file);
		printf("in_pipe = %d\nout_append = %d\n", tmp->in_pipe, tmp->out_append);
		printf("out_trunc = %d\n", tmp->out_trunc);
		printf("out_pipe = %d\nnext = %p\n\n", tmp->out_pipe, tmp->next);
		tmp = tmp->next;
	}
}
