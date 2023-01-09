/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_set_path_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foster <foster@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:13:25 by foster            #+#    #+#             */
/*   Updated: 2023/01/09 15:26:04 by foster           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

static int	check_access(char **arr, t_cati **mini, t_cati *node)
{
	int		i;
	char	*str;

	i = -1;
	while (arr && arr[++i])
	{
		str = ut_strcpy(arr[i]);
		if (!str)
			full_exit(mini, 1);
		str = ut_strjoin(str, "/");
		if (!str)
			return (clean_split(arr), full_exit(mini, 1), 1);
		if (node->cmd)
			str = ut_strjoin(str, node->cmd[0]);
		if (!str)
			return (clean_split(arr), full_exit(mini, 1), 1);
		if (!access(str, R_OK || X_OK))
		{
			node->path_cmd = str;
			return (1);
		}
		free(str);
	}
	return (0);
}

static void	parse_env_path(char **arr, t_cati **mini, t_cati *node)
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
		return ;
	}
	arr = ut_split_char(tmp->var[1], ':');
	if (!arr)
		full_exit(mini, 1);
	if (!check_access(arr, mini, node))
	{
		node->path_cmd = ut_strcpy(node->cmd[0]);
		if (!node->path_cmd)
		{
			clean_split(arr);
			full_exit(mini, 1);
		}
	}
	clean_split(arr);
}

static void	explicit_path_checks(t_cati **mini, t_cati *node)
{
	stat(node->path_cmd, &node->buff);
	if (S_ISDIR(node->buff.st_mode))
	{
		printf("shellnado: %s: Is a directory\n", node->path_cmd);
		full_exit(mini, 126);
	}
	if (access(node->path_cmd, R_OK || X_OK))
	{
		printf("shellnado: %s: %s\n", node->cmd[0], strerror(errno));
		full_exit(mini, errno);
	}
}

static int	explicit_path(t_cati **mini, t_cati *node)
{
	int	i;

	i = -1;
	while (node->cmd && node->cmd[0][++i])
	{
		if (node->cmd[0][i] == '/')
		{
			node->path_cmd = ut_strcpy(node->cmd[0]);
			if (!node->path_cmd)
				full_exit(mini, 1);
			explicit_path_checks(mini, node);
			return (1);
		}
	}
	return (0);
}

void	set_path_cmd(t_cati **mini, t_cati *node)
{
	char	**arr;

	arr = NULL;
	if (node->cmd)
	{
		if (explicit_path(mini, node))
			return ;
		parse_env_path(arr, mini, node);
	}
}
