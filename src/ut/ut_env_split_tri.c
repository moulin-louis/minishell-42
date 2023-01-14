/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_env_split_tri.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foster <foster@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:28:23 by foster            #+#    #+#             */
/*   Updated: 2023/01/14 16:03:54 by foster           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	sort_env(char **str, int size)
{
	int		i;
	int		j;
	char	*str_tmp;

	i = -1;
	while (++i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (strcmp(str[i], str[j]) > 0)
			{
				str_tmp = str[i];
				str[i] = str[j];
				str[j] = str_tmp;
			}
			j++;
		}
	}
}

void	print_export(char **str, t_cati *node)
{
	int		i;
	t_envp	*tmp;

	i = -1;
	while (str[++i])
	{
		tmp = node->envp;
		while (tmp)
		{
			if (strcmp(str[i], tmp->var[0]) == 0)
			{
				printf("declare -x ");
				printf("%s", str[i]);
				if (tmp->var[1])
				{
					printf("=\"");
					printf("%s", tmp->var[1]);
					printf("\"");
				}
				printf("\n");
			}
			tmp = tmp->next;
		}
	}
}

void	ut_env_split_tri(t_cati *node)
{
	int		size;
	char	**test;
	int		i;
	t_envp	*tmp;

	tmp = node->envp;
	size = env_lstsize(&node->envp);
	test = ut_calloc(size + 1, sizeof(char *));
	if (!test)
	{
		ut_putstr_fd("Malloc error when parsing environement\n", 2);
		return ;
	}
	i = 0;
	while (tmp)
	{
		test[i] = tmp->var[0];
		i++;
		tmp = tmp->next;
	}
	sort_env(test, size);
	print_export(test, node);
	free(test);
}
