/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 10:16:50 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/05 10:42:26 by bschoeff         ###   ########.fr       */
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
	if (!mini)
		return (1);
	mini->envp = envp;
	mini->cmd = ut_split("cd /mnt/nfs");
	bi_cd(&mini);
	bi_pwd(&mini);
	clean_mini(&mini);
	return (0);
}
