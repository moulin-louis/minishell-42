/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 17:29:13 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/15 14:45:09 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

static int	str_len(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

static char	*ft_join(char *str, char *buff)
{
	char	*res;
	int		i;
	int		len;

	len = str_len(str);
	i = 0;
	res = ut_calloc(len + 2, 1);
	while (i < len)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = buff[0];
	i++;
	res[i] = '\0';
	if (str)
		free(str);
	return (res);
}

char	*ut_gnl(int fd)
{
	char	buff[1];
	char	*line;
	int		byte;

	byte = 1;
	line = NULL;
	while (byte >= 0)
	{
		byte = read(fd, buff, 1);
		if (!byte)
		{
			line = ft_join(line, buff);
			break ;
		}
		if (buff[0] == '\n')
		{
			line = ft_join(line, buff);
			break ;
		}
		else
			line = ft_join(line, buff);
	}
	return (line);
}
