/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:12:28 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/07 13:02:36 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>


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
	int	status;

	status = 0;
	if ((*mini)->cmd[1])
	{
		status = statouc((*mini)->cmd[1]);
		if ((*mini)->cmd[2])
		{
			printf("bash: exit: too many arguments\n");
			errno = 1;
			return (clean_mini(mini), 1);
		}
	}
	clean_mini(mini);
	exit(status);
}
