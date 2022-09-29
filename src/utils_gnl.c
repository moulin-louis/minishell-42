/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_gnl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 17:29:13 by bschoeff          #+#    #+#             */
/*   Updated: 2022/09/29 13:04:43 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	res = malloc(len + 2);
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

char	*get_next_line(int fd)
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
