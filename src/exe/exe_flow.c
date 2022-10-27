/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_flow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:20:08 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/27 14:32:10 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>

int	exec_cmd(t_cati **mini, t_cati *node)
{
	if (node->builtin)
		return (exe_bi_launcher(mini, node));
	node->ev = exe_parse_env(mini);
	set_fds(mini, node);
	node->pid = fork();
	node->fds->last = node->pid;
	if (!node->pid)
	{
		set_path_cmd(mini, node);
		if (node->outfile)
		{
			dup2(node->out_fd, 1);
			close_pipes(mini);
		}
		if (!access(node->path_cmd, R_OK || X_OK))
			execve(node->path_cmd, node->cmd, node->ev);
		printf("command '%s' not found\n", node->cmd[0]);
		full_exit(mini, 127);
	}
	return (1);
}

