/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:19:57 by bschoeff          #+#    #+#             */
/*   Updated: 2023/01/13 12:17:40 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

static int	change_var(t_envp *tmp)
{
	char	*pwd;
	char	*buff;

	free(tmp->var[1]);
	buff = NULL;
	pwd = NULL;
	pwd = getcwd(buff, 0);
	if (!pwd)
		return (perror("cd change var[1] malloc"), 0);
	tmp->var[1] = pwd;
	return (1);
}

static int	find_node(t_envp *tmp, char *str)
{
	if (ut_strcmp(tmp->var[0], str))
		return (1);
	return (0);
}

static void	change_newpwd(t_cati *node)
{
	t_envp	*tmp;

	tmp = node->envp;
	while (tmp)
	{
		if (find_node(tmp, "PWD"))
		{
			change_var(tmp);
			break ;
		}
		tmp = tmp->next;
	}
}

static void	change_oldpwd(t_cati **mini, t_cati *node)
{
	t_envp	*tmp_pwd;
	t_envp	*tmp_old;

	tmp_pwd = node->envp;
	tmp_old = node->envp;
	while (tmp_pwd && !find_node(tmp_pwd, "PWD"))
		tmp_pwd = tmp_pwd->next;
	while (tmp_old && !find_node(tmp_old, "OLDPWD"))
		tmp_old = tmp_old->next;
	if (!tmp_old)
		return ;
	if (tmp_old->var[1])
		free(tmp_old->var[1]);
	tmp_old->var[1] = ut_strcpy(tmp_pwd->var[1]);
	if (!tmp_old->var[1])
		full_exit(mini, errno);
}

int	bi_cd(t_cati **mini, t_cati *node)
{
	g_status = 0;
	if (!node->cmd[1])
	{
		if (cd_home(mini) == -1)
			return (1);
	}
	else if (chdir(node->cmd[1]) == -1)
	{
		ut_putstr_fd("bash: cd: ", 2);
		ut_putstr_fd(node->cmd[1], 2);
		ut_putstr_fd(": ", 2);
		ut_putstr_fd(strerror(errno), 2);
		ut_putstr_fd("\n", 2);
		g_status = 1;
		return (1);
	}
	change_oldpwd(mini, node);
	change_newpwd(node);
	return (g_status);
}
