/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:20:35 by bschoeff          #+#    #+#             */
/*   Updated: 2022/09/30 11:14:36 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_arg(char *str)
{
	int		i;
	char	*ref;

	ref = "-n";
	if (str[0] != ref[0] || str[1] != ref[1])
		return (1);
	i = 1;
	while (str[++i])
		if (str[i] != ref[1])
			return (1);
	return (0);
}

int	bi_echo(char **args)
{
	int	i;
	int	len;
	int	n_line;

	i = -1;
	n_line = 0;
	if (is_arg(args[0]))
	{
		n_line = 1;
		i++;
	}
	while (args[++i])
	{
		len = 0;
		while (args[i][len])
			len++;
		write(1, args[i], len);
		if (args[i + 1])
			write(1, " ", 1);
	}
	if (n_line)
		write(1, "\n", 1);
	return (0);
}
