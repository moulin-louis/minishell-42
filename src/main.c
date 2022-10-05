/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 10:16:50 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/05 13:27:40 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

static void	init_mini(t_cati **mini)
{
	*mini = malloc(sizeof(t_cati));
	(*mini)->builtin = 0;
	(*mini)->cmd = NULL;
	(*mini)->fds = 0;
	(*mini)->in_file = 0;
	(*mini)->in_heredoc = 0;
	(*mini)->in_pipe = 0;
	(*mini)->next = NULL;
	(*mini)->out_append = 0;
	(*mini)->out_pipe = 0;
	(*mini)->out_append = 0;
	(*mini)->path_cmd = NULL;
	(*mini)->path_file = NULL;
	(*mini)->envp = NULL;
}

int	main(int ac, char **av, char **env)
{
	t_envp	*envp;
	t_cati	*mini;

	(void)ac;
	(void)av;
	envp = NULL;
	if (!ev_build_env(env, &envp))
		return (1);
	mini = NULL;
	init_mini(&mini);
	mini->envp = envp;
	mini->cmd = ut_split("cd /mnt/nfs");
	bi_cd(&mini);
	bi_pwd(&mini);
	clean_mini(&mini);
	clean_env(&envp);
	return (0);
}
