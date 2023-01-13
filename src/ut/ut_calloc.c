/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 14:25:02 by bschoeff          #+#    #+#             */
/*   Updated: 2023/01/13 13:02:05 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

/*Custom calloc*/

int	multi_overflow(int nb, int sz, int *result)
{
	int	temp;
	int	temp2;
	int	i;

	i = 0;
	temp = nb;
	while (i++ < sz - 1)
	{
		temp2 = temp;
		temp += nb;
		if (temp < temp2)
			return (1);
	}
	*result = temp;
	return (0);
}

/*Malloc a ptr of nb * sz bytes, set all the bytes to 0 and return the ptr
Return NULL if fail*/

void	*ut_calloc(int nb, int sz)
{
	void	*ptr;
	int		result;

	result = 0;
	if (multi_overflow(nb, sz, &result))
		return (ut_putstr_fd("overflow problem calloc", 2), NULL);
	ptr = NULL;
	if (!nb || !sz)
		return (ptr);
	ptr = malloc(result);
	if (!ptr)
		return (NULL);
	ut_bzero(ptr, result);
	return (ptr);
}
