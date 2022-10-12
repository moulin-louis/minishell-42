/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 08:55:02 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/12 13:38:59 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static int	pwd_cmp(char *str)
{
	char	*ref;
	int		i;

	ref = "PWD";
	i = -1;
	while (++i < 3)
		if (str[i] != ref[i])
			return (0);
	return (1);
}

static char	*ft_getenv(t_envp *envp)
{
	t_envp	*tmp;

	tmp = envp;
	while (tmp)
	{
		if (pwd_cmp(tmp->var[0]))
			return (tmp->var[1]);
		tmp = tmp->next;
	}
	return (NULL);
}

int	bi_pwd(t_cati **mini)
{
	char	*pwd;
	char	*buff;
	size_t	size;

	pwd = ft_getenv((*mini)->envp);
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
