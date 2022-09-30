/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ev_build_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 11:38:34 by bschoeff          #+#    #+#             */
/*   Updated: 2022/09/30 12:29:11 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	build_env(char **env, t_envp **envp)
{
	if (!*env)
	{
		(*envp)->envp = malloc (sizeof(char *));
		if (!(*envp)->envp)
			return (perror("Env malloc"), 1);
	}
	return (0);
}