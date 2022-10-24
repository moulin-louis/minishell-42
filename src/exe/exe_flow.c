/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_flow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 09:30:58 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/24 15:53:57 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

static int	manage_fds(t_cati **mini, t_cati *node)
{
	(void)mini;
	(void)node;
	return (0);
}

static void	set_elements(t_cati **mini, t_cati *node)
{
	if (node->infile)
	{
		close(node->fds->pfd_1[0]);
		if (dup2(node->fds->in_fd, 0) == -1)
			full_exit(mini, errno);
	}
	if (!node->next && !node->outfile)
		close(node->fds->pfd_1[1]);
	if (node->out_file)
		dup2(node->fds->out_fd, 1);
	if (node->in_pipe)
		dup2(node->fds->pfd_1[0], 0);
	if (node->out_pipe)
		dup2(node->fds->pfd_1[1], 1);
}

int	first_fork(t_cati **mini, t_cati *node)
{
	set_elements(mini, node);
	if (!manage_fds(mini, node))
		return (0);
	if (node->builtin && !node->out_pipe)
		return (exe_bi_launcher(mini, node));
	return (0);
}

int	second_fork(t_cati **mini, t_cati *node)
{
	set_elements(mini, node);
	if (node->builtin && !node->out_pipe)
		return (exe_bi_launcher(mini, node));
	return (0);
}
