/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ev_build_expt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:19:35 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/06 12:32:51 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

static int	case_env(char *env, t_envp **envp)
{
	t_envp	*new;
	char	*ref;
	int		i;

	new = malloc(sizeof(t_envp));
	if (!new)
		return (perror("Env new node malloc"), 0);
	ref = "declare -x ";
	i = 0;
	while (env[i])
		i++;
	new->next = NULL;
	new->var = malloc(i + 12);
	if (!new->var)
		return (0);
	new->var[i + 11] = '\0';
	i = -1;
	while (ref[++i])
		new->var[i] = ref[i];
	i = -1;
	while (env[++i])
		new->var[i + 11] = env[i];
	env_lstaddback(envp, new);
	return (1);
}

int	ev_build_expt(char **env, t_envp **envp)
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
