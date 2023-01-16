/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 09:32:09 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/16 17:10:05 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static int	error_msg(char *str)
{
	g_var.g_status = 1;
	ut_putstr_fd("shellnado: export: \"", 2);
	ut_putstr_fd(str, 2);
	ut_putstr_fd("\": not a valid identifier\n", 2);
	return (0);
}

static int	already_exists(t_cati *node, char *str)
{
	t_envp	*tmp;
	int		i;

	tmp = node->envp;
	i = 0;
	while (str[i] && str[i] != '+' && str[i] != '=')
		i++;
	while (tmp)
	{
		if (!ft_strncmp(tmp->var[0], str, i))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static int	check_compliance(char *str)
{
	int		j;
	int		k;
	char	*ref;

	if (ut_strcmp(str, "="))
		return (error_msg(str));
	if (str[0] >= '0' && str[0] <= '9')
		return (error_msg(str));
	j = -1;
	ref = "!@#$%^&*()`~-|[]{};:,./<>?";
	while (str[++j] && str[j] != '=')
	{
		k = -1;
		while (ref[++k])
		{
			if (ref[k] == str[j])
				return (error_msg(str));
			if (str[j] == '+' && str[j + 1] != '=')
				return (error_msg(str));
		}
	}
	if (j == 0)
		return (error_msg(str));
	return (1);
}

int	bi_export(t_cati *node)
{
	int	i;

	g_var.g_status = 0;
	if (!node->cmd[1] || ut_strcmp(node->cmd[1], "\n") == 1)
	{
		ut_env_split_tri(node);
		return (g_var.g_status);
	}
	i = 0;
	while (node->cmd[++i])
	{
		if (check_compliance(node->cmd[i]))
		{
			if (already_exists(node, node->cmd[i]))
			{
				if (!change_content(node, node->cmd[i]))
					return (g_var.g_status);
			}
			else
				if (!do_the_expt(node, node->cmd[i]))
					return (g_var.g_status);
		}
	}
	return (g_var.g_status);
}
