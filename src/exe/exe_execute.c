/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 09:53:11 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/25 15:22:38 by bschoeff         ###   ########.fr       */
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
		exec_node(mini, tmp);
		if (tmp->next)
		{
			tmp = tmp->next;
			exec_node(mini, tmp);
		}
		tmp = tmp->next;
	}
	return (0);
}
