/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 09:53:11 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/10 10:02:54 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

static int	cmp(char *s1, char *s2)
{
	int	i;

	i = -1;
	while (s1[++i])
		if (s1[i] != s2[i])
			return (0);
	return (1);
}

int	execute(t_cati **mini)
{
	if (cmp("cd", (*mini)->cmd[0]))
		bi_cd(mini);
	else if (cmp("echo", (*mini)->cmd[0]))
		bi_echo(mini);
	else if (cmp("env", (*mini)->cmd[0]))
		bi_env(mini);
	else if (cmp("export", (*mini)->cmd[0]))
		bi_export(mini);
	else if (cmp("pwd", (*mini)->cmd[0]))
		bi_pwd(mini);
	else if (cmp("unset", (*mini)->cmd[0]))
		bi_unset(mini);
	else if (cmp("exit", (*mini)->cmd[0]))
		return (bi_exit(mini));
	return (0);
}
