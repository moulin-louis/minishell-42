/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axldmg <axldmg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:12:28 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/27 21:35:06 by axldmg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

static int	alphanum(char *str)
{
	int	i;

	if (!ut_within_long(str))
		return (0);
	i = -1;
	if (str[0] == '-')
		i++;
	while (str[++i])
		if (str[i] < '0' || str[i] > '9')
			return (0);
	return (1);
}

static unsigned char	statouc(char *str)
{
	int				i;
	unsigned char	n;
	int				sign;

	i = -1;
	n = 0;
	sign = 1;
	if (str[0] == '-')
	{
		sign *= -1;
		i++;
	}
	while (str[++i])
	{
		n *= 10;
		n += str[i] - '0';
	}
	return (n * sign);
}

int	bi_exit(t_cati **mini, t_cati *node)
{
	unsigned char	status;

	status = 0;
	if (node->cmd[1])
	{
		if (!alphanum(node->cmd[1]))
		{
			printf("shellnado: exit: %s: numeric argument required\n",
				node->cmd[1]);
			clean_mini(mini);
			exit(1);
		}
		status = statouc(node->cmd[1]);
		if (node->cmd[2])
		{
			printf("shellnado: exit: too many arguments\n");
			return (1);
		}
	}
	g_status = status;
	return (full_exit(mini, g_status), 0);
}
