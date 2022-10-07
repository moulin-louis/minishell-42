/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:12:28 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/07 12:30:59 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>


static unsigned char	statoc(char *str)
{
	int				i;
	unsigned char	n;

	i = -1;
	n = 0;
	while (str[++i])
	{
		n *= 10;
		n += str[i] - '0';
	}
	printf("%i\n", n);
	return (n);
}

int	bi_exit(t_cati **mini)
{
	int	status;

	if ((*mini)->cmd[2])
	{
		printf("bash: exit: too many arguments\n");
		errno = 1;
		return (1);
	}
	status = 0;
	if ((*mini)->cmd[1])
		status = statoc((*mini)->cmd[1]);
	clean_mini(mini);
	exit(status);
}
