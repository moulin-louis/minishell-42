/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 18:54:39 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/06 15:42:15 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	g_status = 0;
int	g_pid = 1;

int	main(int ac, char **av, char **env)
{
	t_envp	*envp;
	t_fds	fds;

	(void)av;
	if (ac > 1)
		return (printf("./minishell takes no argument\n"), 1);
	envp = NULL;
	fds.ret = 0;
	if (!ev_build_env(env, &envp))
		return (env_lstclear(&envp), 2);
	run_prompt(envp, &fds);
	return (0);
}
