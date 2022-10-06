/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 09:32:09 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/06 13:49:46 by bschoeff         ###   ########.fr       */
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

static void	no_arg(t_cati **mini)
{
	if (!(*mini)->cmd[1])
		display_expt_ev(mini);
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
		return (0);
	new->var[i + 11] = '\0';
	i = -1;
	while (ref[++i])
		new->var[i] = ref[i];
	i = -1;
	while (var[++i])
		new->var[i + 11] = var[i];
	return (1);
}

int	bi_export(t_cati **mini)
{
	int		i;
	t_envp	*new;

	i = 0;
	no_arg(mini);
	while ((*mini)->cmd[++i])
	{
		new = malloc(sizeof(t_envp));
		if (!new)
		{
			perror("export malloc");
			(*mini)->ret++;
			break ;
		}
		new->next = NULL;
		if (is_set((*mini)->cmd[i]))
		{
			new->var = ut_strcpy((*mini)->cmd[i]);
			if (!new->var)
				return (perror("Fatal error export malloc"), (*mini)->ret);
			env_lstaddback(&(*mini)->envp, new);
		}

		if (!is_set((*mini)->cmd[i]))
		{

				return (0);
			(*mini)->ret++;
		}
		else
		{
			if (!set_var(new, (*mini)->cmd[i]))
			{
				(*mini)->ret++;
				break ;
			}
			else
				env_lstaddback(&(*mini)->expt_ev, new);
		}
	}
	return ((*mini)->ret);
}
