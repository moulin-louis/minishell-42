/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 09:32:09 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/06 15:26:22 by bschoeff         ###   ########.fr       */
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

static int	set_var(t_envp *new, char *var)
{
	int		i;
	char	*ref;

	ref = "declare -x ";
	i = 0;
	while (var[i])
		i++;
	new->next = NULL;
	new->var = malloc(i + 12);
	if (!new->var)
		return (perror("new->var malloc"), 0);
	new->var[i + 11] = '\0';
	i = -1;
	while (ref[++i])
		new->var[i] = ref[i];
	i = -1;
	while (var[++i])
		new->var[i + 11] = var[i];
	return (1);
}

static int	proper_export(t_cati **mini, t_envp *new, char *s)
{
	t_envp	*new2;
	t_envp	*tmp;

	tmp = (*mini)->envp;
	while (tmp)
	{
		if (ut_strcmp(tmp->var, s))
		{
			env_lstdelone(&(*mini)->envp, tmp);
			env_lstdelone(&(*mini)->expt_ev, tmp);
		}
		tmp = tmp->next;
	}
	new2 = malloc(sizeof(t_envp));
	if (!new2)
		return (perror("Export new malloc"), 0);
	new2->next = NULL;
	new2->var = ut_strcpy(s);
	if (!new2)
		return (perror("Export new->var malloc"), 0);
	if (!set_var(new, s))
		return (0);
	env_lstaddback(&(*mini)->expt_ev, new);
	env_lstaddback(&(*mini)->envp, new2);
	return (1);
}

int	bi_export(t_cati **mini)
{
	int		i;
	t_envp	*new;
	t_envp	*tmp;

	if (!(*mini)->cmd[1])
		return (display_expt_ev(mini), (*mini)->ret);
	i = 0;
	while ((*mini)->cmd[++i])
	{
		new = malloc(sizeof(t_envp));
		if (!new)
			return (perror("Export new malloc"), (*mini)->ret);
		new->next = NULL;
		if (!is_set((*mini)->cmd[i]))
		{
			if (!set_var(new, (*mini)->cmd[i]))
				return ((*mini)->ret);
			env_lstaddback(&(*mini)->expt_ev, new);
		}
		else
			if (!proper_export(mini, new, (*mini)->cmd[i]))
				return ((*mini)->ret);
	}
	return ((*mini)->ret);
}
