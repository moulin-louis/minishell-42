/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 10:16:50 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/10 11:11:17 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	main(int ac, char **av, char **env)
{
	t_envp	*envp;
	t_envp	*expt_ev;
	t_fds	*fds;

	(void)av;
	if (ac > 1)
		return (printf("./minishell takes no argument, you twat\n"), 1);
	fds = malloc (sizeof(t_fds));
	if (!fds)
		return (2);
	envp = NULL;
	expt_ev = NULL;
	if (!ev_build_env(env, &envp))
		return (3);
	if (!ev_build_expt(env, &expt_ev))
		return (4);
	run_prompt(envp, expt_ev, fds);
	return (0);
}
