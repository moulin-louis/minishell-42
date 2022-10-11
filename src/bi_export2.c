/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 09:25:48 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/11 10:16:54 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

static int	is_declared(char *s, int set)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == '=' && s[i + 1])
			return (1);
	return (0);
}

static void	end_of_string(t_envp *new, int i, int flag)
{
	if (!flag)
	{
		new->var[i + 11] = '"';
		new->var[i + 12] = '"';
		new->var[i + 13] = '\0';
	}
	else
		new->var[i + 11] = '\0';
}

static int	allocate_node(t_envp *new, char *str, int flag)
{
	if (flag)
		new->var = malloc(ut_word_len(str) + 12);
	else
		new->var = malloc(ut_word_len(str) + 14);
	if (!new->var)
		return (perror("export malloc"), 0);
	return (1);
}

int	bi_expt_expt(t_cati **mini, char *str, int set)
{
	t_envp	*new;
	char	*ref;
	int		i;
	int		flag;

	new = malloc(sizeof(t_envp));
	if (!new)
		return (perror("export malloc"), 0);
	new->next = NULL;
	ref = "declare -x ";
	flag = is_declared(str, set);
	if (!allocate_node(new, str, flag))
		return (0);
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
