/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 08:55:02 by bschoeff          #+#    #+#             */
/*   Updated: 2022/09/30 23:53:50 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	bi_pwd(void)
{
	char	*pwd;
	char	*buff;
	size_t	size;

	pwd = getenv("PWD");
	if (!pwd)
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
	return (printf("%s\n", pwd), 0);
}
