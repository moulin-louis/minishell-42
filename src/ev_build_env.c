/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ev_build_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 11:38:34 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/13 11:52:04 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

/* static int	case_no_env(t_envp **envp)
{
	t_envp	*new1;
	t_envp	*new2;
	t_envp	*new3;

	new1 = malloc(sizeof(t_envp));
	new2 = malloc(sizeof(t_envp));
	new3 = malloc(sizeof(t_envp));
	if (!new1 || !new2 || !new3)
		return (perror("Env build malloc"), 0);
	if (!set(new1, 1) || !set(new2, 2) || !set(new3, 3))
		return (perror("Env build malloc"), 0);
	env_lstaddback(envp, new1);
	env_lstaddback(envp, new2);
	env_lstaddback(envp, new3);
	return (1);
} */

static int	case_env(char *env, t_envp **envp)
{
	t_envp	*new;

	new = malloc(sizeof(t_envp));
	if (!new)
		return (perror("Env new node malloc"), 0);
	new->next = NULL;
	new->var = ut_env_split(env);
	if (!new->var)
		return (perror("Env new node malloc"), 0);
	env_lstaddback(envp, new);
	return (1);
}

int	ev_build_env(char **env, t_envp **envp)
{
	int		i;

	if (!*env)
	{
		//if (!case_no_env(envp))
			return (0);
	}
	else
	{
		i = -1;
		while (env[++i])
			if (!case_env(env[i], envp))
				return (0);
	}
	return (1);
}
