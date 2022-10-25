/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 09:53:11 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/25 16:08:18 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <wait.h>
#include <fcntl.h>

static int	exec_node(t_cati **mini, t_cati *node)
{
	if (!node->out_pipe)
		return (exec_cmd(mini, node));
	else
		exec_node(mini, node->next);
	return (0);
}

int	execute(t_cati **mini)
{
	t_cati	*tmp;

	tmp = *mini;
	exec_node(mini, tmp);
	return (0);
}
