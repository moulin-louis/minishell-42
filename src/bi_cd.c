/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:19:57 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/05 14:01:45 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static void	join(t_cati *tmp, char *ref, char *pwd)
{
	int	i;

	i = -1;
	while (ref[++i])
		tmp->envp->var[i] = ref[i];
	i = -1;
	while (pwd[++i])
		tmp->envp->var[i + 4] = pwd[i];
	tmp->envp->var[i + 4] = '\0';
}

static int	change_var(t_cati *tmp)
{
	int		i;
	char	*pwd;
	char	*buff;
	char	*ref;

	free(tmp->envp->var);
	i = 1;
	buff = NULL;
	ref = "PWD=";
	pwd = NULL;
	while (!pwd)
	{
		pwd = getcwd(buff, i);
		i++;
	}
	i = ut_word_len(pwd);
	tmp->envp->var = malloc(i + 5);
	if (!tmp->envp->var)
		return (perror("cd change var malloc"), 0);
	join(tmp, ref, pwd);
	free(pwd);
	return (1);
}

static int	find_node(t_cati *tmp)
{
	char	*ref;
	int		i;

	ref = "PWD=";
	i = -1;
	while (ref[++i])
		if (tmp->envp->var[i] != ref[i])
			return (0);
	return (1);
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
