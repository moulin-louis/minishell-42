/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_parse_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:53:46 by bschoeff          #+#    #+#             */
/*   Updated: 2023/01/09 12:54:10 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

static void	populate_ev(t_cati **mini, t_envp *tmp, char **arr, int i)
{
	char	*temp;

	temp = arr[i];
	arr[i] = ut_strcpy(tmp->var[0]);
	free (temp);
	if (!arr[i])
		full_exit(mini, errno);
	temp = arr[i];
	arr[i] = ut_strjoin(arr[i], "=");
	free(temp);
	if (!arr[i])
		full_exit(mini, errno);
	if (tmp->var[1])
	{
		temp = arr[i];
		arr[i] = ut_strjoin(arr[i], tmp->var[1]);
		free(temp);
		if (!arr[i])
			full_exit(mini, errno);
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
		populate_ev(mini, tmp, arr, i);
		i++;
		tmp = tmp->next;
	}
	return (arr);
}
