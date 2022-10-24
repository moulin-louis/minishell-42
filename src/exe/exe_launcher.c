/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_launcher.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:43:55 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/24 15:40:47 by bschoeff         ###   ########.fr       */
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

int	exe_bi_launcher(t_cati **mini, t_cati *node)
{
	if (cmp("cd", node->cmd[0]))
		return (bi_cd(node));
	else if (cmp("echo", node->cmd[0]))
		return (bi_echo(node));
	else if (cmp("env", node->cmd[0]))
		return (bi_env(mini));
	else if (cmp("pwd", node->cmd[0]))
		return (bi_pwd(node));
	else if (cmp("export", node->cmd[0]))
		return (bi_export(node));
	else if (cmp("exit", node->cmd[0]))
		return (bi_exit(mini, node));
	else if (cmp("unset", node->cmd[0]))
		return (bi_unset(mini, node));
	return (0);
}
