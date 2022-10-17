/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ev_build_env2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:21:42 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/17 13:49:20 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static char	*ft_getpwd(void)
{
	char	*pwd;
	char	*buff;
	int		size;

	size = 1;
	pwd = NULL;
	buff = NULL;
	while (!pwd)
	{
		pwd = getcwd(buff, size);
		size++;
	}
	free(buff);
	return (pwd);
}

int	set_new1(t_envp *new1)
{
	new1->var = ut_calloc(3, sizeof(char *));
	if (!new1->var)
		return (0);
	new1->var[0] = ut_calloc(7, 1);
	if (!new1->var[0])
		return (0);
	new1->var[0] = ut_strcpy("OLDPWD");
	new1->var[1] = NULL;
	new1->var[2] = NULL;
	return (1);
}

int	set_new2(t_envp *new2)
{
	new2->var = ut_calloc(3, sizeof(char *));
	if (!new2->var)
		return (0);
	new2->var[0] = ut_strcpy("PWD");
	new2->var[1] = ft_getpwd();
	if (!new2->var[0] || !new2->var[1])
		return (0);
	new2->var[2] = NULL;
	return (1);
}

int	set_new3(t_envp *new3)
{
	new3->var = ut_calloc(3, sizeof(char *));
	if (!new3->var)
		return (0);
	new3->var[0] = ut_strcpy("SHLVL");
	new3->var[1] = ut_strcpy("1");
	if (!new3->var[0] || !new3->var[1])
		return (0);
	new3->var[2] = NULL;
	return (1);
}
