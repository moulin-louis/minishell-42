/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 14:25:02 by bschoeff          #+#    #+#             */
/*   Updated: 2023/01/07 21:48:53 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

/*Custom calloc*/

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
		ut_bzero(ptr, check);
	return (ptr);
}
