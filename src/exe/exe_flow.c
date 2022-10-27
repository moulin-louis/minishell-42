/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_flow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axldmg <axldmg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:20:08 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/27 22:13:40 by axldmg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <fcntl.h>

int	exec_node(t_cati **mini, t_cati *node)
{
	if (node->builtin)
	{
		g_status = exe_bi_launcher(mini, node);
		return (g_status);
	}
	exec_cmd(mini, node);
	waitpid(node->pid, &node->fds->status, 0);
	g_status = WEXITSTATUS(node->fds->status);
	return (0);
}

