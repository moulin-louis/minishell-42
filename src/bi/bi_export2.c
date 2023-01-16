/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:47:45 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/16 17:10:05 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static int	handle_plus_change(t_envp *tmp, char *str)
{
	char	*s;

	s = str;
	while (*s != '=')
		s++;
	s++;
	tmp->var[1] = ut_strjoin(tmp->var[1], s);
	if (!tmp->var[1])
		return (0);
	return (1);
}

static int	check_plus(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '=')
			break ;
	if (str[i - 1] == '+')
		return (1);
	return (0);
}

int	change_content(t_cati *node, char *str)
{
	t_envp	*tmp;
	int		i;

	tmp = node->envp;
	i = 0;
	while (str[i] && str[i] != '+' && str[i] != '=')
		i++;
	while (ft_strncmp(tmp->var[0], str, i))
		tmp = tmp->next;
	if (check_plus(str))
	{
		if (!handle_plus_change(tmp, str))
			return (0);
	}
	else
	{
		clean_split(tmp->var);
		tmp->var = ut_env_split(str);
		if (!tmp->var)
			return (0);
	}
	return (1);
}

int	do_the_expt(t_cati *node, char *str)
{
	t_envp	*new;

	new = ut_calloc(1, sizeof(t_envp));
	if (!new)
		return (perror("Envp new node malloc"), 0);
	new->next = NULL;
	new->var = ut_env_split(str);
	if (!new->var)
		return (perror("Env new node malloc"), 0);
	env_lstaddback(&node->envp, new);
	return (1);
}
