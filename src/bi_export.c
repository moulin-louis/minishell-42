/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 09:32:09 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/12 11:09:04 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

static int	is_set(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '=')
			return (1);
	return (0);
}

static void	display_expt_ev(t_cati **mini)
{
	t_envp	*tmp;

	tmp = (*mini)->expt_ev;
	while (tmp)
	{
		printf("%s\n", tmp->var);
		tmp = tmp->next;
	}
}

static int	var_cmp(char *s1, char *s2, int flag)
{
	int	i;

	i = -1;
	if (!flag)
	{
		while (s1[++i] && s2[i] != '=')
			if (s1[i] != s2[i])
				return (0);
	}
	else
	{
		while (s1[++i] && s2[i] && s2[i] != '=')
			if (s1[i + 11] != s2[i])
				return (0);
	}
	return (1);
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
	tmp = (*mini)->expt_ev;
	while (tmp)
	{
		if (var_cmp(tmp->var, str, 1))
		{
			env_lstdelone(&(*mini)->expt_ev, tmp);
			break ;
		}
		tmp = tmp->next;
	}
}

int	bi_export(t_cati **mini)
{
	int		i;

	if (!(*mini)->cmd[1])
		return (display_expt_ev(mini), (*mini)->ret);
	i = 0;
	while ((*mini)->cmd[++i])
	{
		already_exists(mini, (*mini)->cmd[i]);
		if (!is_set((*mini)->cmd[i]))
		{
			if (!bi_expt_expt(mini, (*mini)->cmd[i], 0))
				(*mini)->ret++;
		}
		else
		{
			if (!bi_expt_expt(mini, (*mini)->cmd[i], 1))
				(*mini)->ret++;
			if (!bi_expt_env(mini, (*mini)->cmd[i]))
				(*mini)->ret++;
		}
	}
	return ((*mini)->ret);
}
