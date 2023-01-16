/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_s1cpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 09:01:34 by loumouli          #+#    #+#             */
/*   Updated: 2022/10/03 11:38:43 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

/*another strdup (idk)*/

char	*ut_strcpy(char *s2)
{
	int		i;
	int		len;
	char	*s1;

	if (!s2)
		return (NULL);
	len = 0;
	while (s2[len])
		len++;
	s1 = ut_calloc(len + 1, 1);
	if (!s1)
		return (ut_putstr_fd("Malloc error in ut_strcpy\n", 2), NULL);
	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}
