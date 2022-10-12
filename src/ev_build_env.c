/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ev_build_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 11:38:34 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/12 12:23:35 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

static int	case_env(char *env, t_envp **envp)
{
	t_envp	*new;

	new = malloc(sizeof(t_envp));
	if (!new)
		return (perror("Env new node malloc"), 0);
	new->next = NULL;
	new->var = ut_split(env);
	if (!new->var)
		return (0);
	env_lstaddback(envp, new);
	return (1);
}

int	ev_build_env(char **env, t_envp **envp)
{
	int		i;

	if (!*env)
		*envp = NULL;
	else
	{
		i = -1;
		while (env[++i])
			if (!case_env(env[i], envp))
				return (0);
	}
	return (1);
}
