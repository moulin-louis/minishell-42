/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:42:31 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/12 15:22:36 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

static int	var_cmp(char *s1, char *s2, int flag)
{
	int	i;

	i = 0;
	if (!flag)
	{
		while (s2[i] && (s2[i] == s1[i]))
			i++;
		if (s1[i] == '=')
			return (1);
	}
	else
	{
		while (s2[i] && (s2[i] == s1[i + 11]))
			i++;
		if (!s1[i + 11] || s1[i + 11] == '=')
			return (1);
	}
	return (0);
}

static void	already_exists(t_cati **mini, char *str)
{
	t_envp	*tmp;

	tmp = (*mini)->envp;
	while (tmp)
	{
		if (var_cmp(tmp->var, str, 0))
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
