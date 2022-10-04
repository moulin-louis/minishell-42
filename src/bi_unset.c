/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:42:31 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/04 20:24:10 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

static void	delone(t_envp *tmp)
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

static void	remove_node(t_envp *envp, t_envp *tmp)
{
	t_envp	*iter;

	iter = envp;
	if (!tmp->next)
		delone(tmp);
	while (iter->next != tmp)
		iter = iter->next;
	iter->next = tmp->next;
	delone(tmp);
}

int	bi_unset(t_cati **mini, char *str)
{
	t_envp	*tmp;
	t_envp	*del;
	int		i;

	if (!((*mini)->cmd = ut_split(str)))
		return (perror("unset split malloc"), 1);
	if (!(*mini)->cmd[0])
		return (1);
	i = 0;
	while ((*mini)->cmd[++i])
	{
		tmp = (*mini)->envp;
		while (tmp)
		{
			if (pathcmp(tmp->var, (*mini)->cmd[i]))
			{
				del = tmp;
				tmp = tmp->next;
				remove_node((*mini)->envp, del);
				break ;
			}
			else
				tmp = tmp->next;
		}
	}
	return (0);
}
