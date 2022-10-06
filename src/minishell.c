/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 10:16:50 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/06 13:50:43 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

static int	cmp(char *s1, char *s2)
{
	int	i;

	i = -1;
	while (s1[++i])
		if (s1[i] != s2[i])
			return (0);
	return (1);
}

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
	(*mini)->ret = 0;
}

int	main(int ac, char **av, char **env)
{
	t_envp	*envp;
	t_envp	*expt_ev;
	t_cati	*mini;

	(void)ac;
	(void)av;
	envp = NULL;
	expt_ev = NULL;
	if (!ev_build_env(env, &envp))
		return (1);
	if (!ev_build_expt(env, &expt_ev))
		return (1);
	mini = NULL;
	init_mini(&mini);
	mini->envp = envp;
	mini->expt_ev = expt_ev;
	mini->cmd = ut_split(av[1]);
	if (cmp("cd", mini->cmd[0]))
	{
		bi_cd(&mini);
		clean_split(mini->cmd);
		mini->cmd = ut_split("pwd)");
		bi_pwd(&mini);
	}
	else if (cmp("echo", mini->cmd[0]))
		bi_echo(&mini);
	else if (cmp("env", mini->cmd[0]))
		bi_env(&mini);
	else if (cmp("export", mini->cmd[0]))
	{
		bi_export(&mini);
		clean_split(mini->cmd);
		mini->cmd = ut_split("export");
		bi_export(&mini);
	}
	else if (cmp("pwd", mini->cmd[0]))
		bi_pwd(&mini);
	else if (cmp("unset", mini->cmd[0]))
	{
		bi_unset(&mini);
		clean_split(mini->cmd);
		mini->cmd = ut_split("env");
		bi_env(&mini);
	}
	clean_mini(&mini);
	clean_env(&envp);
	clean_env(&expt_ev);
	return (0);
}
