/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_strinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 16:09:51 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/08 14:14:39 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

/*insert target in result starting at index i*/

void	trigger_insert(char *result, int *i, char *target, int *status)
{
	int	x;

	x = 0;
	while (target[x])
	{
		result[*i] = target[x];
		(*i)++;
		x++;
	}
	*status = 1;
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

void	custom_strlen(char *str, int *x)
{
	*x += ft_strlen(str);
}

/*Replace target str in og str by payload str*/

char	*ut_strinsert(char *og, char *trgt, char *pld)
{
	char	*result;
	int		var[3];

	if (!og || !trgt || !pld)
		return (NULL);
	result = malloc(((ft_strlen(og) - ft_strlen(trgt)) + ft_strlen(pld)) + 1);
	if (!result)
		return (NULL);
	result[((ft_strlen(og) - ft_strlen(trgt)) + ft_strlen(pld))] = '\0';
	var[0] = 0;
	var[1] = 0;
	var[2] = 0;
	while (var[0] < ((ft_strlen(og) - ft_strlen(trgt)) + ft_strlen(pld)))
	{
		if (og[var[1]] == '$' && !var[2])
		{
			if (is_target(og, var[0], trgt))
			{
				trigger_insert(result, &var[0], pld, &var[2]);
				custom_strlen(trgt, &var[1]);
			}
		}
		else
			result[var[0]++] = og[var[1]++];
	}
	return (free(og), free(trgt), free(pld), result);
}
