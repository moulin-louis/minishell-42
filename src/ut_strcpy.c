/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_s1cpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschoeff <bschoeff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 09:01:34 by bschoeff          #+#    #+#             */
/*   Updated: 2022/10/03 11:38:43 by bschoeff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

int	ft_strcpy(char *s1, char *s2)
{
	int		i;
	int		len;

	if (!s2)
		return (1);
	len = 0;
	while (s2[len])
		len++;
	s1 = malloc(len + 1);
	if (!s1)
		return (0);
	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (1);
}
