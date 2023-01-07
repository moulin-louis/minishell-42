/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_env_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 09:55:52 by bschoeff          #+#    #+#             */
/*   Updated: 2023/01/07 21:49:42 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

/*All sort of utilts for t_envp linked list*/

/*Add t_envp node to the back of t_envp linked list*/

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

/*Clear all t_envp linkef list from the ptr*/

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

/*Clean one node of t_envp linked list*/

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

/*Return the len of t_envp linked list*/

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
