/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:19:57 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/12 13:36:08 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static int	change_var(t_cati *tmp)
{
	int		i;
	char	*pwd;
	char	*buff;

	free(tmp->envp->var[1]);
	i = 1;
	buff = NULL;
	pwd = NULL;
	while (!pwd)
	{
		pwd = getcwd(buff, i);
		i++;
	}
	i = ut_word_len(pwd);
	tmp->envp->var[1] = malloc(i);
	if (!tmp->envp->var[1])
		return (perror("cd change var[1] malloc"), 0);
	tmp->envp->var[1] = pwd;
	return (1);
}

static int	find_node(t_cati *tmp)
{
	char	*ref;

	ref = "PWD";
	if (ut_strcmp(tmp->envp->var[0], ref))
		return (1);
	return (0);
}

static void	change_env(t_cati **mini)
{
	t_cati	*tmp;

	tmp = *mini;
	while (tmp->envp)
	{
		if (find_node(tmp))
		{
			change_var(tmp);
			break ;
		}
		tmp->envp = tmp->envp->next;
	}
}

int	bi_cd(t_cati **mini)
{
	if (!(*mini)->cmd || !(*mini)->cmd[1])
		return (0);
	if (chdir((*mini)->cmd[1]) == -1)
		return (perror("cd"), 1);
	change_env(mini);
	return (0);
}
