/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 08:55:02 by bschoeff          #+#    #+#             */
/*   Updated: 2023/01/14 16:32:09 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static char	*ft_getenv(t_envp *envp)
{
	t_envp	*tmp;

	tmp = envp;
	while (tmp)
	{
		if (ut_strcmp(tmp->var[0], "PWD"))
			return (tmp->var[1]);
		tmp = tmp->next;
	}
	return (NULL);
}

int	bi_pwd(t_cati *node)
{
	char	*pwd;
	char	*buff;
	size_t	size;

	g_var.g_status = 0;
	pwd = ft_getenv(node->envp);
	if (pwd)
		return (printf("%s\n", pwd), g_var.g_status);
	else
	{
		size = 1;
		buff = NULL;
		pwd = getcwd(buff, size);
		while (!pwd)
		{
			size++;
			pwd = getcwd(buff, size);
		}
		return (printf("%s\n", pwd), free(pwd), g_var.g_status);
	}
}
