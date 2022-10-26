/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_flow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:20:08 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/26 12:28:36 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <wait.h>

int	exec_cmd(t_cati **mini, t_cati *node)
{
	if (node->builtin)
		return (exe_bi_launcher(mini, node));
	node->ev = exe_parse_env(mini);
	if (!fork())
	{
		set_path_cmd(mini, node);
		if (!access(node->path_cmd, R_OK || X_OK))
			execve(node->path_cmd, node->cmd, node->ev);
		printf("command '%s' not found\n", node->cmd[0]);
		full_exit(mini, 127);
	}
	else
		wait(0);
	return (0);
}
