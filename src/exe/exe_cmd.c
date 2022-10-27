/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axldmg <axldmg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 22:11:57 by axldmg            #+#    #+#             */
/*   Updated: 2022/10/27 22:19:01 by axldmg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <fcntl.h>
#include <errno.h>

void    exec_cmd(t_cati **mini, t_cati *node)
{
    node->ev = exe_parse_env(mini);
	set_fds(mini, node);
	node->pid = fork();
    if (node->pid == -1)
    {
        perror("fork fuck");
        g_status = errno;
        full_exit(mini, g_status);
    }
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
}