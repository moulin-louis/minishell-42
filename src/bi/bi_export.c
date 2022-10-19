/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 09:32:09 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/17 15:55:04 by bschoeff         ###   ########.fr       */
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
		if (tmp->var[1])
		{
			printf("=\"");
			printf("%s", tmp->var[1]);
			printf("\"");
		}
		printf("\n");
		tmp = tmp->next;
	}
}



static int	already_exists(t_cati **mini, char *str)
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
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static int	check_compliance(t_cati **mini, char *str)
{
	int		j;
	int		k;
	char	*ref;

	j = -1;
	ref = "!@#$%^&*()`~-|[]{};:,./<>?";
	while (str[++j] && str[j] != '=')
	{
		k = -1;
		while (ref[++k])
		{
			if (ref[k] == str[j])
			{
				(*mini)->ret++;
				printf("bash: export: \"%s\": not a valid identifier\n", str);
				return (0);
			}
		}
	}
	return (1);
}

int	bi_export(t_cati **mini)
{
	int	i;

	if (!(*mini)->cmd[1])
		return (display_expt_ev(mini), (*mini)->ret);
	i = 0;
	while ((*mini)->cmd[++i])
	{
		if (check_compliance(mini, (*mini)->cmd[i]))
		{
			if (already_exists(mini, (*mini)->cmd[i]))
			{
				if (!change_content(mini, (*mini)->cmd[i]))
					return ((*mini)->ret);
			}
			else
				if (!do_the_expt(mini, (*mini)->cmd[i]))
					return ((*mini)->ret);
		}
	}
	return ((*mini)->ret);
}
