/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:12:28 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/07 13:54:18 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

static int	alphanum(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] <= '0' || str[i] >= '9')
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
	printf("%i\n", (unsigned char)(n * sign));
	return (n * sign);
}

int	bi_exit(t_cati **mini)
{
	if ((*mini)->cmd[1])
	{
		if (!alphanum((*mini)->cmd[1]))
		{
			printf("bash: exit: %s: numeric argument required\n",
				(*mini)->cmd[1]);
			clean_mini(mini);
			exit(2);
		}
		(*mini)->fds->status = statouc((*mini)->cmd[1]);
		if ((*mini)->cmd[2])
		{
			printf("bash: exit: too many arguments\n");
			return (1);
		}
	}
	clean_mini(mini);
	exit((*mini)->fds->status);
}
