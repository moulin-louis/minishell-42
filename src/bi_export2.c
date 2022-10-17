/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:47:45 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/17 15:57:17 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

static int	handle_plus_change(t_cati **mini, char *str)
{
	
}

static int	check_plus(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '=')
			break ;
	if (str[i] == '=' && str[i - 1] == '+')
		return (1);
	return (0);
}

int	change_content(t_cati **mini, char *str)
{
	t_envp *tmp;
	int		i;

	if (check_plus(str))
	{
		if (!handle_plus_change(mini, str))
			return (0);
	}
	else
	{

	}
}

int	do_the_expt(t_cati **mini, char *str)
{
	t_envp	*new;

	new = ut_calloc(1, sizeof(t_envp));
	if (!new)
		return (perror("Envp new node malloc"), 0);
	new->next = NULL;
	new->var = ut_env_split(str);
	if (!new->var)
		return (perror("Env new node malloc"), 0);
	env_lstaddback(&(*mini)->envp, new);
	return (1);
}
