/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axldmg <axldmg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:42:31 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/27 22:05:16 by axldmg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

static void	already_exists(t_cati **mini, char *str)
{
	t_envp	*tmp;

	tmp = (*mini)->envp;
	while (tmp)
	{
		if (ut_strcmp(tmp->var[0], str))
		{
			env_lstdelone(&(*mini)->envp, tmp);
			break ;
		}
		tmp = tmp->next;
	}
}

int	bi_unset(t_cati **mini, t_cati *node)
{
	int		i;

	if (!node->cmd[1])
		return (1);
	i = 0;
	while (node->cmd[++i])
		already_exists(mini, node->cmd[i]);
	return (0);
}
