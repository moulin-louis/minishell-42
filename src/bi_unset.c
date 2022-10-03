/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:42:31 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/03 15:46:10 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static  void	delone(t_envp *tmp)
{
	if (tmp->var)
		free(tmp->var);
	free(tmp);
}

static int	pathcmp(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	while (s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s1[i] != '=')
		return (0);
	return (1);
}

static void	remove_node(t_envp **envp, t_envp *tmp)
{
	t_envp	*iter;

	if (!tmp->next)
		delone(tmp);
	iter = *envp;
	while (iter->next != tmp)
		iter = iter->next;
	iter->next = tmp->next;
	delone(tmp);
}

int	bi_unset(t_envp **envp, char *var)
{
	t_envp	*tmp;

	if (!var || !*var)
		return (1);
	tmp = *envp;
	while (tmp)
	{
		if (pathcmp(tmp->var, var))
			return (remove_node(envp, tmp), 0);
		tmp = tmp->next;
	}
	return (0);
}
