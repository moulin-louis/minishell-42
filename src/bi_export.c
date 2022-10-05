/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 09:32:09 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/05 15:27:18 by bschoeff         ###   ########.fr       */
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

int	bi_export(t_cati **mini)
{
	int		i;
	int		ret;
	t_envp	*new;

	i = 0;
	ret = 0;
	if (!(*mini)->cmd[1])
		return (display_expt_ev(mini), ret);
	while ((*mini)->cmd[++i])
	{
		new = malloc(sizeof(t_envp));
		if (!new)
		{
			printf("%s ", (*mini)->cmd[i]);
			perror("export malloc");
			ret++;
			break ;
		}
		new->next = NULL;
		new->var = ut_strcpy((*mini)->cmd[i]);
		if (!new->var)
			return (perror("Fatal error export malloc"), ret);
		if (is_set((*mini)->cmd[i]))
			env_lstaddback(&(*mini)->envp, new);
		else
			env_lstaddback(&(*mini)->expt_ev, new);
	}
	return (ret);
}
