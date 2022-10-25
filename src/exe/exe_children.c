/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_children.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 08:23:18 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/25 14:36:08 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

static int	access_check(t_cati **mini, t_cati *node, char *path)
{
	path = ut_strjoin(path, "/");
	if (!path)
	{
		printf("Malloc error in buid_path\n");
		full_exit(mini, 1);
	}
	if (!path)
	{
		printf("Malloc error in buid_path\n");
		full_exit(mini, 1);
	}
	path = ut_strjoin(path, node->cmd[0]);
	if (!access(path, R_OK || X_OK))
	{
		node->path_cmd = ut_strcpy(path);
		if (!node->path_cmd)
			return (printf("Malloc error in buid_path\n"), 0);
		return (1);
	}
	return (0);
}

static int	build_path(t_cati **mini, t_cati *node)
{
	char	**paths;
	t_envp	*tmp;
	int		i;

	tmp = node->envp;
	paths = NULL;
	while (tmp)
	{
		if (ut_strcmp(tmp->var[0], "PATH"))
		{
			paths = ut_split_char(tmp->var[1], ':');
			if (!paths)
			{
				printf("Malloc error while buildiing paths\n");
				full_exit(mini, 1);
			}
			break ;
		}
		tmp = tmp->next;
	}
	i = -1;
	while (paths[++i])
	{
		if (access_check(mini, node, paths[i]))
			return (free(paths), 1);
	}
	if (paths)
		clean_split(paths);
	return (0);
}

static int	set_path_cmd(t_cati **mini, t_cati *node)
{
	int	i;

	i = -1;
	while (node->cmd[0][++i])
	{
		if (node->cmd[0][i] == '/')
		{
			node->path_cmd = node->cmd[0];
			return (1);
		}
	}
	if (build_path(mini, node))
		return (1);;
	return (0);
}

static void	check_execv(t_cati **mini, t_cati *node)
{
	if (!set_path_cmd(mini, node))
	{
		printf("Command '%s' not found.\n", node->cmd[0]);
		full_exit(mini, 1);
	}
	if (access(node->path_cmd, R_OK || X_OK))
	{
		printf("shellnado: %s: %s", node->cmd[0], strerror(errno));
		full_exit(mini, errno);
	}
}

void	exe_child(t_cati **mini, t_cati *node)
{
	node->ev = exe_parse_env(mini);
	if (!node->builtin || node->out_pipe)
	{
		check_execv(mini, node);
		if (execve(node->path_cmd, node->cmd, node->ev) == -1)
			full_exit(mini, errno);
	}
	else
		full_exit(mini, exe_bi_launcher(mini, node));
}
