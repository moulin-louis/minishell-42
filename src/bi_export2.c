/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 09:25:48 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/07 11:33:14 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

static void	end_of_string(t_envp *new, int i, int flag)
{
	if (flag)
	{
		new->var[i + 11] = '"';
		new->var[i + 12] = '"';
		new->var[i + 13] = '\0';
	}
	else
		new->var[i + 11] = '\0';
}

int	bi_expt_expt(t_cati **mini, char *str, int flag)
{
	t_envp	*new;
	char	*ref;
	int		i;

	new = malloc(sizeof(t_envp));
	if (!new)
		return (perror("export malloc"), 0);
	new->next = NULL;
	ref = "declare -x ";
	if (!flag)
		new->var = malloc(ut_word_len(str) + 12);
	else
		new->var = malloc(ut_word_len(str) + 14);
	if (!new->var)
		return (perror("export malloc"), 0);
	i = -1;
	while (ref[++i])
		new->var[i] = ref[i];
	i = -1;
	while (str[++i])
		new->var[i + 11] = str[i];
	end_of_string(new, i, flag);
	env_lstaddback(&(*mini)->expt_ev, new);
	return (1);
}

int	bi_expt_env(t_cati **mini, char *str)
{
	t_envp	*new;
	int		i;

	new = malloc(sizeof(t_envp));
	if (!new)
		return (perror("export malloc"), 0);
	new->next = NULL;
	new->var = malloc(ut_word_len(str) + 1);
	if (!new->var)
		return (perror("export malloc"), 0);
	i = -1;
	while (str[++i])
		new->var[i] = str[i];
	new->var[i] = '\0';
	env_lstaddback(&(*mini)->envp, new);
	return (1);
}
