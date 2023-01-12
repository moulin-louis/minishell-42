/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foster <foster@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:12:28 by bschoeff          #+#    #+#             */
/*   Updated: 2023/01/12 17:14:09 by foster           ###   ########.fr       */
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
	if (str[0] == '-' || str[0] == '+')
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

int	len_option(char **cmd)
{
	int	len;

	len = 0;
	if (!cmd)
		return (0);
	while (cmd[len])
		len++;
	return (len);
}

int	bi_exit(t_cati **mini, t_cati *node)
{
	unsigned char	status;

	status = 0;
	if (node->cmd[1] && !alphanum(node->cmd[1]))
	{
		ut_putstr_fd("bash: exit: ", 2);
		ut_putstr_fd(node->cmd[1], 2);
		ut_putstr_fd(": numeric argument required\n", 2);
		full_exit(mini, 2);
	}
	if (len_option(node->cmd) != 1 && len_option(node->cmd) != 2)
		return (ut_putstr_fd("bash: exit: too many arguments\n", 2), 1);
	if (node->cmd[1])
	{
		if (ut_strcmp(node->cmd[1], "-0") || ut_strcmp(node->cmd[1], "+0"))
			full_exit(mini, 0);
		status = statouc(node->cmd[1]);
	}
	return (g_status = status, full_exit(mini, g_status), g_status);
}
