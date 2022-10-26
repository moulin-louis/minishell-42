/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_set_path_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 10:39:44 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/26 12:26:19 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static int	check_access(char **arr, t_cati **mini, t_cati *node)
{
	int		i;
	char	*str;

	i = -1;
	while (arr[++i])
	{
		str = ut_strjoin(arr[i], "/");
		if (!str)
			full_exit(mini, 1);
		str = ut_strjoin(str, node->cmd[0]);
		if (!str)
			full_exit(mini, 1);
		if (!access(str, R_OK || X_OK))
		{
			node->path_cmd = str;
			return (1);
		}
		free(str);
	}
	return (0);
}

static int	parse_env_path(char **arr, t_cati **mini, t_cati *node)
{
	t_envp	*tmp;

	tmp = node->envp;
	while (tmp && !ut_strcmp(tmp->var[0], "PATH"))
		tmp = tmp->next;
	if (!tmp)
	{
		node->path_cmd = ut_strcpy(node->cmd[0]);
		if (!node->path_cmd)
			full_exit(mini, 1);
		return (0);
	}
	arr = ut_split_char(tmp->var[1], ':');
	if (!arr)
		return (full_exit(mini, 1), 1);
	if (!check_access(arr, mini, node))
	{
		node->path_cmd = ut_strcpy(node->cmd[0]);
		if (!node->path_cmd)
			full_exit(mini, 1);
		return (0);
	}
	return (1);
}

static int	explicit_path(t_cati **mini, t_cati *node)
{
	int	i;

	i = -1;
	while (node->cmd[0][++i])
	{
		if (node->cmd[0][i] == '/')
		{
			node->path_cmd = ut_strcpy(node->cmd[0]);
			if (!node->path_cmd)
				full_exit(mini, 1);
			if (!access(node->path_cmd, R_OK || X_OK))
				return (1);
			printf("bash: %s: No such file or directory\n", node->cmd[0]);
			full_exit(mini, 127);
		}
	}
	return (0);
}

void	set_path_cmd(t_cati **mini, t_cati *node)
{
	char	**arr;

	arr = NULL;
	if (explicit_path(mini, node) || !parse_env_path(arr, mini, node))
		return ;
}
