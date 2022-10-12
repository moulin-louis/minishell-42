/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 09:32:09 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/12 15:18:56 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

static void	display_expt_ev(t_cati **mini)
{
	t_envp	*tmp;

	tmp = (*mini)->envp;
	while (tmp)
	{
		printf("declare -x ");
		printf("%s", tmp->var[0]);
		printf("=\"");
		if (tmp->var[1])
			printf("%s", tmp->var[1]);
		printf("\"\n");
		tmp = tmp->next;
	}
}

static int	do_the_expt(t_cati **mini, char *str)
{
	t_envp	*new;

	new = malloc(sizeof(t_envp));
	if (!new)
		return (perror("Envp new node malloc"), 0);
	new->next = NULL;
	new->var = ut_env_split(str);
	if (!new->var)
		return (perror("Env new node malloc"), 0);
	env_lstaddback(&(*mini)->envp, new);
	return (1);
}

static void	already_exists(t_cati **mini, char *str)
{
	t_envp	*tmp;
	int		i;

	tmp = (*mini)->envp;
	while (tmp)
	{
		i = -1;
		while (str[++i] && str[i] != '=')
			if (tmp->var[0][i] != str[i])
				break ;
		if (tmp->var[0][i] == '\0' && (str[i] == '\0' || str[i] == '='))
		{
			env_lstdelone(&(*mini)->envp, tmp);
			break ;
		}
		tmp = tmp->next;
	}
}

int	bi_export(t_cati **mini)
{
	int	i;

	if (!(*mini)->cmd[1])
		return (display_expt_ev(mini), (*mini)->ret);
	i = 0;
	while ((*mini)->cmd[++i])
	{
		already_exists(mini, (*mini)->cmd[i]);
		if (!do_the_expt(mini, (*mini)->cmd[i]))
			return ((*mini)->ret);
	}
	return ((*mini)->ret);
}
