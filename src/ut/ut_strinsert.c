/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_strinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 16:09:51 by loumouli          #+#    #+#             */
/*   Updated: 2022/12/10 16:48:23 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

/*insert target in result starting at index i*/

void	trigger_insert(char *result, int *i, char *target)
{
	int	x;

	x = 0;
	while (target[x])
	{
		result[*i] = target[x];
		(*i)++;
		x++;
	}
}

/*check if target str is in og str from i position*/

int	is_target(char *og, int i, char *target)
{
	int	x;

	x = 0;
	while (target[x] && og[i])
	{
		if (target[x] != og[i])
			return (0);
		x++;
		i++;
	}
	return (1);
}

/*Replace target str in og str by payload str*/

char	*ut_strinsert(char *og, char *target, char *payload)
{
	char	*result;
	int		len;
	int		i;
	int		x;

	len = (ft_strlen(og) - ft_strlen(target)) + ft_strlen(payload);
	result = malloc(len + 1);
	if (!result)
		return (free(payload), free(target), NULL);
	result[len] = '\0';
	i = 0;
	x = 0;
	while (i < len)
	{
		if (og[x] == '$')
		{
			if (is_target(og, i, target))
				trigger_insert(result, &i, payload);
			x += ft_strlen(target);
		}
		else
			result[i++] = og[x++];
	}
	return (free(og), free(target), free(payload), result);
}
