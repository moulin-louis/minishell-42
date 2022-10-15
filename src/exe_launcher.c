/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_launcher.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:43:55 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/15 13:00:10 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	len(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

static int	cmp(char *s1, char *s2)
{
	int	i;
	int	ls1;
	int	ls2;

	i = -1;
	ls1 = len(s1);
	ls2 = len(s2);
	if (ls1 != ls2)
		return (0);
	while (s1[++i])
		if (s1[i] != s2[i])
			return (0);
	return (1);
}

int	bi_launcher(t_cati **mini)
{
	if (cmp("cd", (*mini)->cmd[0]))
		bi_cd(mini);
	else if (cmp("echo", (*mini)->cmd[0]))
		bi_echo(mini);
	else if (cmp("env", (*mini)->cmd[0]))
		bi_env(mini);
	else if (cmp("pwd", (*mini)->cmd[0]))
		bi_pwd(mini);
	else if (cmp("export", (*mini)->cmd[0]))
		bi_export(mini);
	else if (cmp("exit", (*mini)->cmd[0]))
		return (bi_exit(mini));
	else if (cmp("unset", (*mini)->cmd[0]))
		return (bi_unset(mini));
	return (0);
}
