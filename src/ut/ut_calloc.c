/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 14:25:02 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/15 14:48:14 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stddef.h>

static void	bzr(void *s, int n)
{
	char	*str;

	str = s;
	while (n)
	{
		*str = '\0';
		str++;
		n--;
	}
}

void	*ut_calloc(int nb, int sz)
{
	void	*ptr;
	int		check;

	check = nb * sz;
	ptr = NULL;
	if (!nb || !sz || check / nb != sz)
		return (ptr);
	ptr = malloc(nb * sz);
	if (ptr)
		bzr(ptr, check);
	return (ptr);
}
