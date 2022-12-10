/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 14:25:02 by bschoeff          #+#    #+#             */
/*   Updated: 2022/12/10 16:59:39 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stddef.h>

/*Custom calloc*/

/*set the n first bytes of s ptr to 0*/

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

/*Malloc a ptr of nb * sz bytes, set all the bytes to 0 and return the ptr
Return NULL if fail*/

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
