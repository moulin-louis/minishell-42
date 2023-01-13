/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_parse_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:53:46 by bschoeff          #+#    #+#             */
/*   Updated: 2023/01/13 12:22:21 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <errno.h>

int	populate_ev(t_cati **mini, t_envp *tmp, char **arr, int i)
{
	char	*temp;

	temp = arr[i];
	arr[i] = ut_strcpy(tmp->var[0]);
	if (!arr[i])
		return (arr[i] = temp, clean_split(arr), full_exit(mini, errno), 1);
	free (temp);
	temp = arr[i];
	arr[i] = ut_strjoin(arr[i], "=");
	if (!arr[i])
		return (arr[i] = temp, clean_split(arr), full_exit(mini, errno), 1);
	free(temp);
	if (tmp->var[1])
	{
		temp = arr[i];
		arr[i] = ut_strjoin(arr[i], tmp->var[1]);
		if (!arr[i])
		{
			arr[i] = temp;
			return (clean_split(arr), full_exit(mini, errno), 1);
		}
		free(temp);
	}
	return (0);
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
		ut_putstr_fd("Malloc error when parsing environement\n", 2);
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
