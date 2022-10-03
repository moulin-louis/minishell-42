/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ev_build_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 11:38:34 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/03 11:40:24 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

/* static int	case_no_env(t_envp **envp)
{
	t_envp	*new;

	new = NULL;
	if (!lstnew(new))
		return (0);
	new->var = NULL;
	*envp = new;
	return (1);
} */

static int	case_env(t_envp **envp, char *env)
{
	t_envp *new;

	new = NULL;
	if (!lstnew(new))
		return (0);
	if (!ft_strcpy(new->var, env))
		return (perror("build_env strcpy malloc"), 0);
	printf("new->var in build_env: %s\n", new->var);
	lstaddback(envp, new);
	return (1);
}

int	ev_build_env(char **env, t_envp **envp)
{
	int	i;

	if (!*env)
		*envp = NULL;
	else
	{
		i = -1;
		while (env[++i])
			if (!case_env(envp, env[i]))
				return (0);
	}
	return (1);
}
