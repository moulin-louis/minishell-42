/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:20:35 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/05 09:54:30 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>

static int	is_arg(char *str)
{
	int		i;
	char	*ref;

	ref = "-n";
	if (str[0] != ref[0] || str[1] != ref[1])
		return (1);
	if (str[2])
	{
		i = 1;
		while (str[++i])
			if (str[i] != ref[1])
				return (1);
	}
	return (0);
}

int	bi_echo(t_cati **mini)
{
	int	i;
	int	len;
	int	n_line;

	i = 0;
	n_line = 1;
	if (!is_arg((*mini)->cmd[1]))
	{
		n_line = 0;
		i++;
	}
	while ((*mini)->cmd[++i])
	{
		len = 0;
		while ((*mini)->cmd[i][len])
			len++;
		write(1, (*mini)->cmd[i], len);
		if ((*mini)->cmd[i + 1])
			write(1, " ", 1);
	}
	if (n_line)
		write(1, "\n", 1);
	return (0);
}
