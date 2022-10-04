/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_clean_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 12:36:37 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/04 14:26:55 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	clean_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		i++;
	while (--i >= 0)
		free(arr[i]);
	free(arr);
}

void	clean_env(t_envp **envp)
{
	env_lstclear(envp);
}

void	clean_mini(t_cati **mini)
{
	t_cati *tmp;

	if (!*mini)
		return ;
	while (*mini)
	{
		tmp = *mini;
		*mini = (*mini)->next;
		if (tmp->cmd)
			clean_split(tmp->cmd);
		if (tmp->path_cmd)
			free(tmp->path_cmd);
		if (tmp->path_file)
			free(tmp->path_cmd);
		free(tmp);
	}
}
