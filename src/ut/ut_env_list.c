/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_env_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foster <foster@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 09:55:52 by bschoeff          #+#    #+#             */
/*   Updated: 2023/01/11 20:12:37 by foster           ###   ########.fr       */
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

void	env_delone(t_envp *node)
{
	clean_split(node->var);
	free(node);
}

/*Clean one node of t_envp linked list*/

void	env_lstdelone(t_envp **envp, t_envp *node)
{
	t_envp	*tmp;

	tmp = *envp;
	while (tmp)
	{
		if (tmp->next == node)
		{
			tmp->next = node->next;
			if (node->var)
				clean_split(node->var);
			free(node);
			return ;
		}
		tmp = tmp->next;
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
