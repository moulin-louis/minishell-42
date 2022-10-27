/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axldmg <axldmg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 08:55:02 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/27 22:05:13 by axldmg           ###   ########.fr       */
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

	pwd = ft_getenv(node->envp);
	if (pwd)
		return (printf("%s\n", pwd), 0);
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
		return (printf("%s\n", pwd), free(pwd), 0);
	}
}
