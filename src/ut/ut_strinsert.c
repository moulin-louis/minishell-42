/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_strinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 16:09:51 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/13 12:28:47 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <string.h>

void	custom_strlen(const char *str, int *x)
{
	*x += ft_strlen(str);
}

/*insert target in result starting at index i*/

void	trigger_insert(char *result, int var[], const char *pld,
		const char *trgt)
{
	int	x;

	x = 0;
	while (pld[x])
	{
		result[var[0]] = pld[x];
		var[0]++;
		x++;
	}
	var[2] = 1;
	custom_strlen(trgt, &var[1]);
}

/*check if target str is in og str from i position*/

int	is_target(const char *og, int i, const char *target)
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

char	*ut_strinsert(const char *og, char *trgt, const char *pld)
{
	char	*result;
	int		var[5];

	result = malloc(((ft_strlen(og) - ft_strlen(trgt)) + ft_strlen(pld)) + 1);
	if (!result)
		return (free((char *)trgt), free((char *)pld), NULL);
	result[((ft_strlen(og) - ft_strlen(trgt)) + ft_strlen(pld))] = '\0';
	memset(var, 0, sizeof(var));
	while (var[0] < ((ft_strlen(og) - ft_strlen(trgt)) + ft_strlen(pld)))
	{
		if (og[var[1]] == '\"')
			var[4]++;
		if (og[var[1]] == '\'' && !(var[4] % 2))
			var[3]++;
		if (og[var[1]] == '$' && !var[2] && !(var[3] % 2))
		{
			if (is_target(og, var[0], trgt) && !(var[3] % 2))
				trigger_insert(result, var, pld, trgt);
		}
		else
			result[var[0]++] = og[var[1]++];
	}
	return (free((char *)og), free((char *)trgt), free((char *)pld), result);
}
