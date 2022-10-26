/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_parse_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:53:46 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/26 09:03:11 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

static void	populate_ev(t_cati **mini, t_envp *tmp, char **arr, int i)
{
	arr[i] = ut_strcpy(tmp->var[0]);
	arr[i] = ut_strjoin(arr[i], "=");
	if (tmp->var[1])
		arr[i] = ut_strjoin(arr[i], tmp->var[1]);
	if (!arr[i])
	{
		printf("Malloc error when parsing environement\n");
		clean_mini(mini);
		exit(2);
	}
}

char	**exe_parse_env(t_cati **mini)
{
	t_envp	*tmp;
	int		size;
	char	**arr;
	int		i;

	tmp = (*mini)->envp;
	size = env_lstsize(&(*mini)->envp);
	arr = ut_calloc(size + 1, sizeof(char *));
	if (!arr)
	{
		printf("Malloc error when parsing environement\n");
		full_exit(mini, 2);
	}
	i = 0;
	while (tmp)
	{
		size = ut_word_len(tmp->var[0]);
		if (tmp->var[1])
			size += ut_word_len(tmp->var[1]);
		populate_ev(mini, tmp, arr, i);
		i++;
		tmp = tmp->next;
	}
	return (arr);
}
