/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_env_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 09:55:52 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/17 10:24:32 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

void	env_lstaddback(t_envp **envp, t_envp *new)
{
	t_envp	*tmp;

	if (!*envp)
	{
		*envp = new;
		return ;
	}
	tmp = *envp;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	env_lstclear(t_envp **envp)
{
	t_envp	*tmp;

	while (*envp)
	{
		tmp = *envp;
		*envp = (*envp)->next;
		if (tmp->var)
			clean_split(tmp->var);
		free(tmp);
	}
}

void	env_lstdelone(t_envp **envp, t_envp *tmp)
{
	t_envp	*tmp2;

	tmp2 = *envp;
	while (tmp2)
	{
		if (tmp2->next == tmp)
		{
			tmp2->next = tmp->next;
			if (tmp->var)
				free(tmp->var);
			free(tmp);
		}
		if (tmp2)
			tmp2 = tmp2->next;
	}
}

int	env_lstsize(t_envp **envp)
{
	t_envp	*tmp;
	int		i;

	tmp = *envp;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
