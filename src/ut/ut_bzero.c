/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 21:43:15 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/07 21:43:44 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Set the n bytes of s as 0*/

void	ut_bzero(void *s, int n)
{
	char	*temp;

	temp = s;
	while (n)
	{
		*temp = 0;
		temp++;
		n--;
	}
}
