/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 10:16:50 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/04 11:34:52 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	main(int ac, char **av, char **env)
{
	t_envp	*envp;
	t_cati	*mini;

	(void)ac;
	(void)av;
	envp = NULL;
	if (!ev_build_env(env, &envp))
		return (1);
	mini = malloc(sizeof(t_cati));
	mini->envp = envp;
	mini->cmd = ft_split("env");
	bi_env(&mini);
	clean_split(mini->cmd);
	mini->cmd = ft_split("export JOHN=coucou PATRICK");
	bi_export(&mini);
	clean_split(mini->cmd);
	mini->cmd = ft_split("env");
	bi_env(&mini);
	clean_env(&mini->envp);
	clean_split(mini->cmd);
	free(mini);
	return (0);
}
