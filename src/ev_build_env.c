/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ev_build_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 11:38:34 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/03 09:00:11 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

static int	case_no_env(t_envp *envp)
{
	envp->envp = malloc (sizeof(char *));
	if (!envp->envp)
		return (perror("Env array malloc"), 0);
	envp->envp[0] = NULL;
	return (1);
}

static int	case_env(t_envp *envp, char **env, int i)
{
	envp->envp = malloc(sizeof(char *) * (i + 1));
	if (!envp->envp)
		return (perror("Env chart malloc"), clean_split(envp->envp), 0);
	envp->envp[i] = 0;
	while (--i >= 0)
	{
		envp->envp[i] = ft_strcpy(env[i]);
		if (!envp->envp[i])
			return (perror("Envp table malloc"), clean_split(envp->envp), 0);
	}
	return (1);
}

int	ev_build_env(char **env, t_envp *envp)
{
	int	i;

	if (!*env)
	{
		if (!case_no_env(envp))
			return (0);
	}
	else if (*env)
	{
		i = 0;
		while (env[i])
			i++;
		if (!case_env(envp, env, i))
			return (0);
	}
	return (1);
}
