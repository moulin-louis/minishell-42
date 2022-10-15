/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:42:31 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/15 12:59:07 by bschoeff         ###   ########.fr       */
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

int	bi_unset(t_cati **mini)
{
	int		i;

	if (!(*mini)->cmd[1])
		return (1);
	i = 0;
	while ((*mini)->cmd[++i])
		already_exists(mini, (*mini)->cmd[i]);
	return (0);
}
