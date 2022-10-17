/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 10:16:50 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/17 10:29:21 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	main(int ac, char **av, char **env)
{
	t_envp	*envp;
	t_fds	fds;

	(void)av;
	if (ac > 1)
		return (printf("./minishell takes no argument, you twat\n"), 1);
	envp = NULL;
	if (!ev_build_env(env, &envp))
		return (env_lstclear(&envp), 2);
	run_prompt(envp, &fds);
	return (0);
}
