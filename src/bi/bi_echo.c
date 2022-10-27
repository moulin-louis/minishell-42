/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axldmg <axldmg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:20:35 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/27 20:57:43 by axldmg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>

static int	check_expand(t_cati *node)
{
	if (ut_strcmp(node->cmd[1], "$?"))
		return (printf("%i\n", g_status), 1);
	return (0);
}

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

static int	write_stuff(t_cati *node)
{
	int	i;
	int	len;
	int	n_line;

	i = 0;
	n_line = 1;
	while (node->cmd[++i])
	{
		if (!is_arg(node->cmd[1]))
		{
			n_line = 0;
			while (!is_arg(node->cmd[i]))
				i++;
		}
		len = 0;
		while (node->cmd[i][len])
			len++;
		write(1, node->cmd[i], len);
		if (node->cmd[i + 1])
			write(1, " ", 1);
	}
	return (n_line);
}

int	bi_echo(t_cati *node)
{
	int	n_line;

	g_status = 0;
	if (check_expand(node))
		return (g_status);
	n_line = write_stuff(node);
	if (n_line)
		write(1, "\n", 1);
	return (g_status);
}
