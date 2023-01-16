/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 18:54:39 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/16 14:49:09 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

t_glob	g_var;

int	main(int ac, char **av, char **env)
{
	t_envp	*envp;
	t_fds	fds;

	(void)av;
	memset(&fds, 0, sizeof(fds));
	if (ac > 1)
		return (printf("./minishell takes no argument\n"), 1);
	envp = NULL;
	if (!ev_build_env(env, &envp))
		return (env_lstclear(&envp), 2);
	run_prompt(envp, &fds);
	return (0);
}
